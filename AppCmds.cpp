////////////////////////////////////////////////////////////////////////////////
//! \file   AppCmds.cpp
//! \brief  The AppCmds class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "AppCmds.hpp"
#include "AboutDlg.hpp"
#include "ClassGenApp.hpp"
#include <WCL/File.hpp>
#include "Params.hpp"
#include <Core/AnsiWide.hpp>
#include <WCL/StrCvt.hpp>
#include <Core/ParseException.hpp>
#include <Core/StringUtils.hpp>
#include <malloc.h>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

AppCmds::AppCmds()
	: WCL::NullCmdController()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

AppCmds::~AppCmds()
{
}

#if (__GNUC__ >= 8) // GCC 8+
// error: format '%hs' expects argument of type 'short int*', but argument 3 has type 'const char*' [-Werror=format=]
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
#endif

////////////////////////////////////////////////////////////////////////////////
//! Generate the source file from the template.

bool AppCmds::generateFile(const CPath& templateFile, CPath& targetFile, const Params& params)
{
	// Check template file exists.
	if (!templateFile.Exists())
	{
		g_app.AlertMsg(TXT("The template file is missing:\n\n%s"), templateFile.c_str());
		return false;
	}

	// Check target file doesn't exist.
	if (targetFile.Exists())
	{
		if (g_app.QueryMsg(TXT("The target file already exists:\n\n%s\n\nDo you want to overwrite it?"), targetFile.c_str()) != IDYES)
			return false;
	}

	// Copy template to target file.
	if (!CFile::Copy(templateFile, targetFile, true))
	{
		g_app.AlertMsg(TXT("Failed to create target file:\n\n%s\n\n%s"), targetFile.c_str(), CStrCvt::FormatError().c_str());
		return false;
	}

	try
	{
		// Ensure target file is writable.
		DWORD attributes = targetFile.Attributes();

		if (attributes & FILE_ATTRIBUTE_READONLY)
			targetFile.SetAttributes(attributes & (~FILE_ATTRIBUTE_READONLY));

		CFile file;

		file.Open(targetFile, GENERIC_READWRITE);

		// Get the files size.
		size_t size = static_cast<size_t>(file.Size());

		// Allocate zero terminated code buffer.
		char* code = static_cast<char*>(_alloca(size+1));

		// Read file contents into tmp buffer.
		file.Read(code, size);
		code[size] = '\0';

		// Reset for writing.
		file.Seek(0, CFile::BEGIN);

		char* end = code + size;

		// For all characters...
		while (*code != '\0')
		{
			// Finds the next parameter to substitute.
			char* paramBegin = strstr(code, "${");

			// No more parameters to handle?
			if (paramBegin == nullptr)
			{
				// Write the rest of the file.
				file.Write(code, end - code);

				code = end;
			}
			else // (param != nullptr)
			{
				// Write the code up to the parameter.
				file.Write(code, paramBegin - code);

				// Find the end of the parameter name.
				paramBegin += 2;

				char* paramEnd = strstr(paramBegin, "}");

				// Parameter to substitue?
				if (paramEnd != nullptr)
				{
					std::string param(paramBegin, paramEnd-paramBegin);

					if (!params.exists(A2T(param)))
						throw Core::ParseException(Core::fmt(TXT("Invalid parameter string found:\n\n${%hs}"), param.c_str()));

					std::string value(T2A(params.find(A2T(param))));

					// Write the substituted value.
					file.Write(value.c_str(), value.length());

					code = paramEnd+1;
				}
				else // (paramEnd == nullptr)
				{
					// Invalid parameter, skip passed token.
					code++;
				}
			}
		}

		file.SetEOF();
		file.Close();
	}
	catch (const Core::Exception& e)
	{
		g_app.AlertMsg(TXT("Failed to parse target file:\n\n%s\n\n%s"), targetFile.c_str(), e.twhat());
		return false;
	}

	return true;
}

#if (__GNUC__ >= 8) // GCC 8+
#pragma GCC diagnostic pop
#endif
