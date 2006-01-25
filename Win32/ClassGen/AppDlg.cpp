/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APPDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAppDlg class definition.
**
*******************************************************************************
*/

#include "AppHeaders.hpp"

/******************************************************************************
** Method:		Default constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CAppDlg::CAppDlg()
	: CMainDlg(IDD_MAIN)
{

	DEFINE_CTRL_TABLE
		CTRL(IDC_TEMPLATE,		&m_cbTemplate)
		CTRL(IDC_COMPONENT,		&m_cbComponent)
		CTRL(IDC_CLASS_NAME,	&m_ebClassName)
		CTRL(IDC_FOLDER,		&m_cbFolder)
		CTRL(IDC_HPP_FILE,		&m_ebHPPFile)
		CTRL(IDC_CPP_FILE,		&m_ebCPPFile)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_TEMPLATE,	CBN_SELCHANGE,	OnSelectTemplate)
		CMD_CTRLMSG(IDC_CLOSE,		BN_CLICKED,		OnClose)
		CMD_CTRLMSG(IDC_BROWSE,		BN_CLICKED,		OnBrowse)
		CMD_CTRLMSG(IDC_CLASS_NAME,	EN_CHANGE,		OnEditClassName)
		CMD_CTRLMSG(IDC_GENERATE,	BN_CLICKED,		OnGenerate)
	END_CTRLMSG_TABLE
}

/******************************************************************************
** Method:		OnInitDialog()
**
** Description:	Initialise the dialog.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnInitDialog()
{
	if (App.m_aoTemplates.empty())
	{
		AlertMsg("There are no templates defined.");
		App.m_AppWnd.Close();
		return;
	}

	if (App.m_aoComponents.empty())
	{
		AlertMsg("There are no components defined.");
		App.m_AppWnd.Close();
		return;
	}

	// Load template names combo.
	for (uint i = 0; i < App.m_aoTemplates.size(); ++i)
		m_cbTemplate.Add(App.m_aoTemplates[i]->m_strName, i);

	// Select 1st template by default.
	m_cbTemplate.CurSel(m_cbTemplate.FindExact(App.m_aoTemplates[0]->m_strName));

	OnSelectTemplate();

	// Load component names combo.
	for (uint i = 0; i < App.m_aoComponents.size(); ++i)
		m_cbComponent.Add(App.m_aoComponents[i]->m_strName, i);

	// Select 1st component by default.
	m_cbComponent.CurSel(m_cbComponent.FindExact(App.m_aoComponents[0]->m_strName));

	// Load last used folders combo.
	for (int i = 0; i < App.m_astrFolders.Size(); ++i)
		AddFolderName(App.m_astrFolders[i], false);

	// Initialise with last settings.
	AddFolderName(App.m_strLastFolder, true);
}

/******************************************************************************
** Method:		OnDestroy()
**
** Description:	Window being destroyed, save any preferences.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnDestroy()
{
	// Use path as starting point for next selection.
	App.m_strLastFolder = m_cbFolder.Text();
}

/******************************************************************************
** Method:		OnClose()
**
** Description:	Close the application.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnClose()
{
	App.m_AppWnd.Close();
}

/******************************************************************************
** Method:		OnSelectTemplate()
**
** Description:	Template selection changed.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnSelectTemplate()
{
	// Get the selected template.
	int nSel  = m_cbTemplate.CurSel();
	int nItem = m_cbTemplate.ItemData(nSel);

	CTemplatePtr pTemplate = App.m_aoTemplates[nItem];

	// Get fields expected.
	bool bIsClass = pTemplate->m_bNeedsClass;
	bool bHasHPP  = (pTemplate->m_strHPPFile != "");
	bool bHasCPP  = (pTemplate->m_strCPPFile != "");

	// Update controls.
	m_ebClassName.Enable(bIsClass);

	if (!bIsClass)
		m_ebClassName.Text("");

	m_ebHPPFile.Enable(bHasHPP);

	if (!bHasHPP)
		m_ebHPPFile.Text("");

	m_ebCPPFile.Enable(bHasCPP);

	if (!bHasCPP)
		m_ebCPPFile.Text("");
}

/******************************************************************************
** Method:		OnEditClassName()
**
** Description:	Class name changed, update the hpp and cpp file names.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnEditClassName()
{
	CString strClassName = m_ebClassName.Text();

	// Strip 'C' prefix, if present.
	if ( (strClassName.Length() > 0) && (strClassName[0] == 'C') )
		strClassName.Delete(0);

	// Set the filenames.
	if (m_ebHPPFile.IsEnabled())
		m_ebHPPFile.Text(strClassName + ".hpp");

	if (m_ebCPPFile.IsEnabled())
		m_ebCPPFile.Text(strClassName + ".cpp");
}

/******************************************************************************
** Method:		OnBrowse()
**
** Description:	Browse for the hpp/cpp file destination folder.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnBrowse()
{
	CPath strFolder = m_cbFolder.Text();

	// If folder name empty start from last path.
	if (strFolder == "")
		strFolder = App.m_strLastFolder;

	// Select the folder.
	if (!strFolder.SelectDir(*this, "Select The Destination Folder", strFolder))
		return;

	// Display path.
	AddFolderName(strFolder, true);
}

/******************************************************************************
** Method:		AddFolderName()
**
** Description:	Add the folder name to the combo if it doesn't already exist.
**				Make if the selection, if required.
**
** Parameters:	strName		The folder name.
**				bSelect		Make it the selection.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::AddFolderName(const CString& strName, bool bSelect)
{
	// Discard if empty.
	if (strName.Empty())
		return;

	// Already exists?
	int nPos = m_cbFolder.FindExact(strName);

	if (nPos == CB_ERR)
		nPos = m_cbFolder.Add(strName);

	// Make it selection?
	if (bSelect)
		m_cbFolder.CurSel(nPos);
}

/******************************************************************************
** Method:		OnGenerate()
**
** Description:	Generate the class.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppDlg::OnGenerate()
{
	// Get the selected template.
	int nTemplSel  = m_cbTemplate.CurSel();
	int nTemplItem = m_cbTemplate.ItemData(nTemplSel);

	CTemplatePtr pTemplate = App.m_aoTemplates[nTemplItem];

	// Get the selected template.
	int nComptSel  = m_cbComponent.CurSel();
	int nComptItem = m_cbComponent.ItemData(nComptSel);

	CComponentPtr pComponent = App.m_aoComponents[nComptItem];

	// Get expected fields.
	bool bIsClass = pTemplate->m_bNeedsClass;
	bool bHasHPP  = (pTemplate->m_strHPPFile != "");
	bool bHasCPP  = (pTemplate->m_strCPPFile != "");

	// Validate class name.
	CString strClassName = m_ebClassName.Text();

	if (bIsClass && strClassName.Empty())
	{
		AlertMsg("You must supply a name for the class.");
		m_ebClassName.Focus();
		return;
	}

	// Validate folder.
	CPath strFolder = m_cbFolder.Text();

	if (!strFolder.Exists())
	{
		AlertMsg("The destination folder is invalid.");
		m_cbFolder.Focus();
		return;
	}

	// Validate HPP file name, if expected.
	CPath strHPPFile = m_ebHPPFile.Text();

	if (bHasHPP && strHPPFile.Empty())
	{
		AlertMsg("You must supply the HPP file name.");
		m_ebHPPFile.Focus();
		return;
	}

	// Validate CPP file name, if expected.
	CPath strCPPFile = m_ebCPPFile.Text();

	if (bHasCPP && strCPPFile.Empty())
	{
		AlertMsg("You must supply the CPP file name.");
		m_ebCPPFile.Focus();
		return;
	}

	CParams oParams;

	oParams.Set("CLASS",     strClassName);
	oParams.Set("INCLUDE",   pComponent->m_strInclude);
	oParams.Set("COMPONENT", pComponent->m_strComment);
	oParams.Set("NAMESPACE", pComponent->m_strNamespace);

	// Generate HPP file, if required.
	if (pTemplate->m_strHPPFile != "")
	{
		CPath strTemplateFile = CPath(App.m_strTmplFolder, pTemplate->m_strHPPFile);

		oParams.Set("File", strHPPFile.FileTitle());
		oParams.Set("FILE", strHPPFile.FileTitle().ToUpper());

		if (!GenerateFile(strTemplateFile, CPath(strFolder, strHPPFile), oParams))
			return;
	}

	// Generate CPP file, if required.
	if (pTemplate->m_strCPPFile != "")
	{
		CPath strTemplateFile = CPath(App.m_strTmplFolder, pTemplate->m_strCPPFile);

		oParams.Set("File", strHPPFile.FileTitle());
		oParams.Set("FILE", strCPPFile.FileTitle().ToUpper());

		if (!GenerateFile(strTemplateFile, CPath(strFolder, strCPPFile), oParams))
			return;
	}

	// Add folder to MRU list.
	if (App.m_astrFolders.Find(strFolder, true) == -1)
		App.m_astrFolders.Add(strFolder);

	if (!strClassName.Empty())
		NotifyMsg("%s class generated.", strClassName);
	else
		NotifyMsg("%s file generated.", strHPPFile);
}

/******************************************************************************
** Method:		GenerateFile()
**
** Description:	Generate a target file from a template.
**
** Parameters:	strTemplateFile		The template filename.
**				strTargetFile		The target filename.
**				oParams				The substitution parameters.
**
** Returns:		true or false.
**
*******************************************************************************
*/

bool CAppDlg::GenerateFile(const CPath& strTemplateFile, const CPath& strTargetFile, const CParams& oParams)
{
	// Check template file exists.
	if (!strTemplateFile.Exists())
	{
		AlertMsg("The template file is missing:\n\n%s", strTemplateFile);
		return false;
	}

	// Check template file is writable.
	if (strTemplateFile.ReadOnly())
	{
		AlertMsg("The template file is write-protected:\n\n%s", strTemplateFile);
		return false;
	}

	// Check target file doesn't exist.
	if (strTargetFile.Exists())
	{
		if (QueryMsg("The target file already exists:\n\n%s\n\nDo you want to overwrite it?", strTargetFile) != IDYES)
			return false;
	}

	// Copy template to target file.
	if (!CFile::Copy(strTemplateFile, strTargetFile, true))
	{
		AlertMsg("Failed to create target file:\n\n%s", strTargetFile);
		return false;
	}

	try
	{
		CFile oFile;

		oFile.Open(strTargetFile, GENERIC_READWRITE);

		// Get the files size.
		ulong lSize = oFile.Size();

		// Allocate zero terminated code buffer.
		char* pszCode = (char*) _alloca(lSize+1);

		// Read file contents into tmp buffer.
		oFile.Read(pszCode, lSize);
		pszCode[lSize] = '\0';

		// Reset for writing.
		oFile.Seek(0, FILE_BEGIN);

		char* pszEnd = pszCode + lSize;

		// For all characters...
		while (*pszCode != '\0')
		{
			// Finds the next parameter to substitute.
			char* pszParam = strchr(pszCode, '$');

			// No more parameters to handle?
			if (pszParam == NULL)
			{
				// Write the rest of the file.
				oFile.Write(pszCode, pszEnd - pszCode);

				pszCode = pszEnd;
			}
			else // (pszParam != NULL)
			{
				// Write the code up to the parameter.
				oFile.Write(pszCode, pszParam - pszCode);

				// Find the end of the parameter name.
				char* pszParamEnd = strchr(pszParam+1, '$');

				// Parameter to substitue?
				if (pszParamEnd != NULL)
				{
					CString strParam(pszParam+1, pszParamEnd-pszParam-1);
					CString strValue(oParams.Find(strParam));

					// Write the rest of the file.
					oFile.Write(strValue, strValue.Length());

					pszCode = pszParamEnd+1;
				}
				else // (pszParamEnd == NULL)
				{
					// Invalid parameter, skip passed token.
					pszCode++;
				}
			}
		}

		oFile.SetEOF();
		oFile.Close();
	}
	catch (CFileException& e)
	{
		AlertMsg("Failed to parse target file:\n\n%s\n\nReason: %s", strTargetFile, e.ErrorText());
		return false;
	}

	return true;
}
