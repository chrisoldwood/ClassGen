////////////////////////////////////////////////////////////////////////////////
//! \file   ClassGenApp.cpp
//! \brief  The ClassGenApp class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "ClassGenApp.hpp"
#include <Core/ConfigurationException.hpp>
#include <Core/StringUtils.hpp>
#include <WCL/AppConfig.hpp>
#include <limits>

#ifdef __GNUG__

#include <WCL/WinMain.hpp>

////////////////////////////////////////////////////////////////////////////////
//! This is the real (C SDK) entry point for a Windows application.

extern "C" int WINAPI WinMain(HINSTANCE hInstance,
							  HINSTANCE /*hPrevInstance*/,
							  LPSTR     lpszCmdLine,
							  int       nCmdShow)
{
	return WCL::winMain(hInstance, lpszCmdLine, nCmdShow);
}

#endif //__GNUG__

////////////////////////////////////////////////////////////////////////////////
// Global variables.

//! The application object.
CClassGenApp g_app;

////////////////////////////////////////////////////////////////////////////////
// Constants.

const tchar* TEMPLATES_FILE	   = TXT("Templates.ini");
const tchar* TEMPLATES_VERSION = TXT("2.0");
const tchar* SETTINGS_VERSION  = TXT("2.0");
const tchar* PUBLISHER         = TXT("Chris Oldwood");
const tchar* APPLICATION       = TXT("Class Generator");

////////////////////////////////////////////////////////////////////////////////
//! Default constructor

CClassGenApp::CClassGenApp()
	: CApp(m_appWnd, m_appCmds)
	, m_templatesFolder(TXT("."))
	, m_headerExt(TXT(".hpp"))
	, m_sourceExt(TXT(".cpp"))
	, m_author(TXT("The Author"))
{

}

////////////////////////////////////////////////////////////////////////////////
//! Destructor

CClassGenApp::~CClassGenApp()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Handle application startup.

bool CClassGenApp::OnOpen()
{
	// Set the app title.
	m_strTitle = APPLICATION;

	try
	{
		// Load settings.
		loadConfig();
	}
	catch (const Core::Exception& e)
	{
		FatalMsg(TXT("Failed to configure the application:-\n\n%s"), e.twhat());
		return false;
	}

	// Create the main window.
	if (!m_appWnd.Create())
		return false;

	// Show it.
	m_appWnd.Centre();
	m_appWnd.Show(m_iCmdShow);

	// Update UI.
	m_appCmds.InitialiseUI();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//! Handle application shutdown.

bool CClassGenApp::OnClose()
{
	try
	{
		// Save settings.
		saveConfig();
	}
	catch (const Core::Exception& e)
	{
		FatalMsg(TXT("Failed to save the application configuration:-\n\n%s"), e.twhat());
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
//! Load the application settings.

void CClassGenApp::loadConfig()
{
	CIniFile templatesFile(CPath::ApplicationDir() / TEMPLATES_FILE);

	if (!templatesFile.m_strPath.Exists())
		throw Core::ConfigurationException(Core::fmt(TXT("The configuration file is missing:-\n\n%s"), templatesFile.m_strPath.c_str()));

	// Read the templates file version.
	CString templatesVer = templatesFile.ReadString(TXT("Version"), TXT("Version"), TEMPLATES_VERSION);

	if (templatesVer != TEMPLATES_VERSION)
		throw Core::ConfigurationException(Core::fmt(TXT("The configuration file is incompatible:-\n\n%s"), templatesFile.m_strPath.c_str()));

	// Read the general settings.
	m_headerExt = templatesFile.ReadString(TXT("General"), TXT("HppExt"), m_headerExt);
	m_sourceExt = templatesFile.ReadString(TXT("General"), TXT("CppExt"), m_sourceExt);
	m_author = templatesFile.ReadString(TXT("General"), TXT("Author"), m_author);

	// Read the templates settings.
	m_templatesFolder = templatesFile.ReadString(TXT("Templates"), TXT("Path"), m_templatesFolder);

	if (m_templatesFolder.Empty())
		m_templatesFolder = CPath::ApplicationDir();

	size_t count = templatesFile.ReadInt(TXT("Templates"), TXT("Count"), 0);

	if (count == 0)
		throw Core::ConfigurationException(TXT("No templates have been defined."));

	for (size_t i = 0; i < count; ++i)
	{
		tstring entry = Core::fmt(TXT("Template[%u]"), i);
		tstring name  = templatesFile.ReadString(TXT("Templates"), entry, tstring());

		// Valid template name?
		if (!name.empty())
		{
			TemplatePtr item(new Template);
			tstring     section = name + TXT(" Template");

			item->m_name        = name;
			item->m_description = templatesFile.ReadString(section, TXT("Description"), TXT(""));
			item->m_isClass     = templatesFile.ReadBool  (section, TXT("Class"), true);
			item->m_headerFile  = templatesFile.ReadString(section, TXT("HPP"), TXT(""));
			item->m_sourceFile  = templatesFile.ReadString(section, TXT("CPP"), TXT(""));

			m_templates.push_back(item);
		}
	}

	// Read the component names.
	count = templatesFile.ReadInt(TXT("Components"), TXT("Count"), 0);

	if (count == 0)
		throw Core::ConfigurationException(TXT("No components have been defined."));

	for (size_t i = 0; i < count; ++i)
	{
		tstring entry = Core::fmt(TXT("Component[%d]"), i);
		tstring name  = templatesFile.ReadString(TXT("Components"), entry, tstring());

		// Valid component name?
		if (!name.empty())
		{
			ComponentPtr item(new Component);
			tstring      section = name + TXT(" Component");

			item->m_name        = name;
			item->m_description = templatesFile.ReadString(section, TXT("Description"), TXT(""));
			item->m_include     = templatesFile.ReadString(section, TXT("Include"),   TXT(""));
			item->m_comment     = templatesFile.ReadString(section, TXT("Comment"),   TXT(""));
			item->m_namespace   = templatesFile.ReadString(section, TXT("Namespace"), TXT(""));
			item->m_folder      = templatesFile.ReadString(section, TXT("Folder"),    TXT(""));

			m_components.push_back(item);
		}
	}

	WCL::AppConfig settings(PUBLISHER, APPLICATION);

	// Read the templates file version.
	tstring settingsVer = settings.readString(settings.DEFAULT_SECTION, TXT("Version"), SETTINGS_VERSION);

	if (settingsVer != SETTINGS_VERSION)
		throw Core::ConfigurationException(Core::fmt(TXT("The configuration data is incompatible - '%s'"), settingsVer.c_str()));

	const size_t max = std::numeric_limits<size_t>::max();

	// Read the list of folders used.
	for (size_t i = 0; i != max; ++i)
	{
		tstring entry  = Core::fmt(TXT("%u"), i);
		tstring folder = settings.readString(TXT("Folders"), entry, TXT(""));

		if (folder.empty())
			break;

		if (m_mruFolders.Find(folder.c_str(), true) == Core::npos)
			m_mruFolders.Add(folder.c_str());
	}

	// Read the last use settings.
	m_lastComponent = settings.readString(settings.DEFAULT_SECTION, TXT("LastComponent"), m_lastComponent);
	m_lastFolder    = settings.readString(settings.DEFAULT_SECTION, TXT("LastFolder"), m_lastFolder);
}

////////////////////////////////////////////////////////////////////////////////
//! Save the application settings.

void CClassGenApp::saveConfig()
{
	WCL::AppConfig settings(PUBLISHER, APPLICATION);

	// Write the file version.
	settings.writeString(settings.DEFAULT_SECTION, TXT("Version"), SETTINGS_VERSION);

	// Write the list of folders used.
	settings.deleteSection(TXT("Folders"));

	for (size_t i = 0; i != m_mruFolders.Size(); ++i)
	{
		tstring entry = Core::fmt(TXT("%u"), i);

		settings.writeString(TXT("Folders"), entry, tstring(m_mruFolders[i]));
	}

	// Write the last use settings.
	settings.writeString(settings.DEFAULT_SECTION, TXT("LastComponent"), m_lastComponent);
	settings.writeString(settings.DEFAULT_SECTION, TXT("LastFolder"), m_lastFolder);
}
