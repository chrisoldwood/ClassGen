////////////////////////////////////////////////////////////////////////////////
//! \file   AppCmds.cpp
//! \brief  The AppCmds class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "AppCmds.hpp"
#include "AboutDlg.hpp"
#include "ClassGenApp.hpp"
#include <WCL/File.hpp>
#include <WCL/FileException.hpp>
#include "Params.hpp"
#include <Core/AnsiWide.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

AppCmds::AppCmds()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

AppCmds::~AppCmds()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Generate the source file from the template.

bool AppCmds::generateFile(const CPath& templateFile, const CPath& targetFile, const Params& params)
{
	// Check template file exists.
	if (!templateFile.Exists())
	{
		g_app.AlertMsg(TXT("The template file is missing:\n\n%s"), templateFile);
		return false;
	}

	// Check template file is writable.
	if (templateFile.ReadOnly())
	{
		g_app.AlertMsg(TXT("The template file is write-protected:\n\n%s"), templateFile);
		return false;
	}

	// Check target file doesn't exist.
	if (targetFile.Exists())
	{
		if (g_app.QueryMsg(TXT("The target file already exists:\n\n%s\n\nDo you want to overwrite it?"), targetFile) != IDYES)
			return false;
	}

	// Copy template to target file.
	if (!CFile::Copy(templateFile, targetFile, true))
	{
		g_app.AlertMsg(TXT("Failed to create target file:\n\n%s"), targetFile);
		return false;
	}

	try
	{
		CFile file;

		file.Open(targetFile, GENERIC_READWRITE);

		// Get the files size.
		ulong size = file.Size();

		// Allocate zero terminated code buffer.
		char* code = static_cast<char*>(_alloca(size+1));

		// Read file contents into tmp buffer.
		file.Read(code, size);
		code[size] = '\0';

		// Reset for writing.
		file.Seek(0, FILE_BEGIN);

		char* end = code + size;

		// For all characters...
		while (*code != '\0')
		{
			// Finds the next parameter to substitute.
			char* paramBegin = strstr(code, "${");

			// No more parameters to handle?
			if (paramBegin == NULL)
			{
				// Write the rest of the file.
				file.Write(code, end - code);

				code = end;
			}
			else // (param != NULL)
			{
				// Write the code up to the parameter.
				file.Write(code, paramBegin - code);

				// Find the end of the parameter name.
				paramBegin += 2;

				char* paramEnd = strstr(paramBegin, "}");

				// Parameter to substitue?
				if (paramEnd != NULL)
				{
					std::string param(paramBegin, paramEnd-paramBegin);

					if (!params.exists(A2T(param)))
					{
						g_app.AlertMsg(TXT("Invalid parameter string:\n\n%hs\n\nFound in template file:\n\n%s"), param.c_str(), templateFile);
						return false;
					}

					std::string value(T2A(params.find(A2T(param))));

					// Write the substituted value.
					file.Write(value.c_str(), value.length());

					code = paramEnd+1;
				}
				else // (paramEnd == NULL)
				{
					// Invalid parameter, skip passed token.
					code++;
				}
			}
		}

		file.SetEOF();
		file.Close();
	}
	catch (CFileException& e)
	{
		g_app.AlertMsg(TXT("Failed to parse target file:\n\n%s\n\nReason: %s"), targetFile, e.What());
		return false;
	}

	return true;
}
