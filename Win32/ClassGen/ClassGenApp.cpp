/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLASSGENAPP.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CClassGenApp class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

// "The" application object.
CClassGenApp App;

/******************************************************************************
**
** Class constants.
**
*******************************************************************************
*/

#ifdef _DEBUG
const char* CClassGenApp::VERSION      = "v1.1 [Debug]";
#else
const char* CClassGenApp::VERSION      = "v1.1";
#endif
const char* CClassGenApp::INI_FILE_VER = "1.0";

/******************************************************************************
** Method:		Constructor
**
** Description:	Default constructor.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CClassGenApp::CClassGenApp()
	: CApp(m_AppWnd, m_AppCmds)
{

}

/******************************************************************************
** Method:		Destructor
**
** Description:	Cleanup.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CClassGenApp::~CClassGenApp()
{
	// Free up collections.
	m_aoTemplates.DeleteAll();
	m_aoComponents.DeleteAll();
}

/******************************************************************************
** Method:		OnOpen()
**
** Description:	Initialises the application.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClassGenApp::OnOpen()
{
	// Set the app title.
	m_strTitle = "Class Generator";

	// Load settings.
	LoadConfig();
	
	// Load the toolbar bitmap.
	m_rCmdControl.CmdBitmap().LoadRsc(IDR_APPTOOLBAR);

	// Create the main window.
	if (!m_AppWnd.Create())
		return false;

	// Show it.
	m_AppWnd.Centre();
	m_AppWnd.Show(m_iCmdShow);

	// Update UI.
	m_AppCmds.UpdateUI();

	return true;
}

/******************************************************************************
** Method:		OnClose()
**
** Description:	Cleans up the application resources.
**
** Parameters:	None.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CClassGenApp::OnClose()
{
	// Save settings.
	SaveConfig();

	return true;
}

/******************************************************************************
** Method:		LoadConfig()
**
** Description:	Load the app configuration.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CClassGenApp::LoadConfig()
{
	// Read the file version.
	CString strVer = m_oIniFile.ReadString("Version", "Version", INI_FILE_VER);

	// Read the template names.
	int nTemplates = m_oIniFile.ReadInt("Templates", "Count", 0);

	for (int i = 0; i < nTemplates; ++i)
	{
		CString strSection;

		strSection.Format("Template[%d]", i);

		CString strTemplate = m_oIniFile.ReadString("Templates", strSection, "");

		// Valid template name?
		if (!strTemplate.Empty())
		{
			CTemplate* pTemplate = new CTemplate;

			pTemplate->m_strName    = strTemplate;
			pTemplate->m_strHPPFile = m_oIniFile.ReadString(strTemplate + " Template", "HPP", "");
			pTemplate->m_strCPPFile = m_oIniFile.ReadString(strTemplate + " Template", "CPP", "");

			m_aoTemplates.Add(pTemplate);
		}
	}

	// Read the component names.
	int nComponents = m_oIniFile.ReadInt("Components", "Count", 0);

	for (i = 0; i < nComponents; ++i)
	{
		CString strSection;

		strSection.Format("Component[%d]", i);

		CString strComponent = m_oIniFile.ReadString("Components", strSection, "");

		// Valid component name?
		if (!strComponent.Empty())
		{
			CComponent* pComponent = new CComponent;

			pComponent->m_strName    = strComponent;
			pComponent->m_strInclude = m_oIniFile.ReadString(strComponent + " Component", "Include", "");
			pComponent->m_strComment = m_oIniFile.ReadString(strComponent + " Component", "Comment", "");

			m_aoComponents.Add(pComponent);
		}
	}

	// Read the list of folders used.
	int nFolders = m_oIniFile.ReadInt("Folders", "Count", 0);

	for (i = 0; i < nFolders; ++i)
	{
		CString strSection;

		strSection.Format("Folder[%d]", i);

		CString strFolder = m_oIniFile.ReadString("Folders", strSection, "");

		if ( (!strFolder.Empty()) && (m_astrFolders.Find(strFolder, true) == -1) )
			m_astrFolders.Add(strFolder);
	}

	// Read the last use settings.
	m_strLastFolder = m_oIniFile.ReadString("Main", "LastFolder", "");
}

/******************************************************************************
** Method:		SaveConfig()
**
** Description:	Save the app configuration.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CClassGenApp::SaveConfig()
{
	// Write the file version.
	m_oIniFile.WriteString("Version", "Version", INI_FILE_VER);

	// Write the list of folders used.
	m_oIniFile.WriteInt("Folders", "Count", m_astrFolders.Size());

	for (int i = 0; i < m_astrFolders.Size(); ++i)
	{
		CString strSection;

		strSection.Format("Folder[%d]", i);

		m_oIniFile.WriteString("Folders", strSection, m_astrFolders[i]);
	}

	// Write the last use settings.
	m_oIniFile.WriteString("Main", "LastFolder", m_strLastFolder);
}
