/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLASSGENAPP.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CClassGenApp class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "ClassGenApp.hpp"

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
const tchar* CClassGenApp::VERSION      = TXT("v1.2 [Debug]");
#else
const tchar* CClassGenApp::VERSION      = TXT("v1.2");
#endif
const tchar* CClassGenApp::INI_FILE_VER = TXT("1.2");

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
	, m_strTmplFolder(TXT("."))
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
	m_strTitle = TXT("Class Generator");

	// Load settings.
	LoadConfig();
	
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
	CString strVer = m_oIniFile.ReadString(TXT("Version"), TXT("Version"), INI_FILE_VER);

	// Read the templates folder.
	m_strTmplFolder = m_oIniFile.ReadString(TXT("Templates"), TXT("Path"), m_strTmplFolder);

	// Read the template names.
	int nTemplates = m_oIniFile.ReadInt(TXT("Templates"), TXT("Count"), 0);

	for (int i = 0; i < nTemplates; ++i)
	{
		CString strSection;

		strSection.Format(TXT("Template[%d]"), i);

		CString strTemplate = m_oIniFile.ReadString(TXT("Templates"), strSection, TXT(""));

		// Valid template name?
		if (!strTemplate.Empty())
		{
			CTemplatePtr pTemplate(new CTemplate);

			pTemplate->m_strName     = strTemplate;
			pTemplate->m_bNeedsClass = m_oIniFile.ReadBool  (strTemplate + TXT(" Template"), TXT("Class"), true);
			pTemplate->m_strHPPFile  = m_oIniFile.ReadString(strTemplate + TXT(" Template"), TXT("HPP"),   TXT(""));
			pTemplate->m_strCPPFile  = m_oIniFile.ReadString(strTemplate + TXT(" Template"), TXT("CPP"),   TXT(""));

			m_aoTemplates.push_back(pTemplate);
		}
	}

	// Read the component names.
	int nComponents = m_oIniFile.ReadInt(TXT("Components"), TXT("Count"), 0);

	for (int i = 0; i < nComponents; ++i)
	{
		CString strSection;

		strSection.Format(TXT("Component[%d]"), i);

		CString strComponent = m_oIniFile.ReadString(TXT("Components"), strSection, TXT(""));

		// Valid component name?
		if (!strComponent.Empty())
		{
			CComponentPtr pComponent(new CComponent);

			pComponent->m_strName      = strComponent;
			pComponent->m_strInclude   = m_oIniFile.ReadString(strComponent + TXT(" Component"), TXT("Include"),   TXT(""));
			pComponent->m_strComment   = m_oIniFile.ReadString(strComponent + TXT(" Component"), TXT("Comment"),   TXT(""));
			pComponent->m_strNamespace = m_oIniFile.ReadString(strComponent + TXT(" Component"), TXT("Namespace"), TXT(""));

			m_aoComponents.push_back(pComponent);
		}
	}

	// Read the list of folders used.
	int nFolders = m_oIniFile.ReadInt(TXT("Folders"), TXT("Count"), 0);

	for (int i = 0; i < nFolders; ++i)
	{
		CString strSection;

		strSection.Format(TXT("Folder[%d]"), i);

		CString strFolder = m_oIniFile.ReadString(TXT("Folders"), strSection, TXT(""));

		if ( (!strFolder.Empty()) && (m_astrFolders.Find(strFolder, true) == -1) )
			m_astrFolders.Add(strFolder);
	}

	// Read the last use settings.
	m_strLastFolder = m_oIniFile.ReadString(TXT("Main"), TXT("LastFolder"), TXT(""));
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
	m_oIniFile.WriteString(TXT("Version"), TXT("Version"), INI_FILE_VER);

	// Write the list of folders used.
	m_oIniFile.WriteInt(TXT("Folders"), TXT("Count"), m_astrFolders.Size());

	for (size_t i = 0; i < m_astrFolders.Size(); ++i)
	{
		CString strSection;

		strSection.Format(TXT("Folder[%d]"), i);

		m_oIniFile.WriteString(TXT("Folders"), strSection, m_astrFolders[i]);
	}

	// Write the last use settings.
	m_oIniFile.WriteString(TXT("Main"), TXT("LastFolder"), m_strLastFolder);
}
