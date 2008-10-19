////////////////////////////////////////////////////////////////////////////////
//! \file   AppDlg.cpp
//! \brief  The AppDlg class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "AppDlg.hpp"
#include "AboutDlg.hpp"
#include "ClassGenApp.hpp"
#include "Params.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

AppDlg::AppDlg()
	: CMainDlg(IDD_MAIN)
{

	DEFINE_CTRL_TABLE
		CTRL(IDC_TEMPLATE,		&m_cbTemplate)
		CTRL(IDC_COMPONENT,		&m_cbComponent)
		CTRL(IDC_CLASS_NAME,	&m_ebClassName)
		CTRL(IDC_FOLDER,		&m_cbFolder)
		CTRL(IDC_HPP_FILE,		&m_ebHPPFile)
		CTRL(IDC_CPP_FILE,		&m_ebCPPFile)
		CTRL(IDC_NAMESPACE,		&m_namespaceEditor)
		CTRL(IDC_COMP_DESC,		&m_componentLabel)
		CTRL(IDC_TMPL_DESC,		&m_templateLabel)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_COMPONENT,	CBN_SELCHANGE,	&AppDlg::OnSelectComponent)
		CMD_CTRLMSG(IDC_TEMPLATE,	CBN_SELCHANGE,	&AppDlg::OnSelectTemplate)
		CMD_CTRLMSG(IDC_CLOSE,		BN_CLICKED,		&AppDlg::OnClose)
		CMD_CTRLMSG(IDC_BROWSE,		BN_CLICKED,		&AppDlg::OnBrowse)
		CMD_CTRLMSG(IDC_CLASS_NAME,	EN_CHANGE,		&AppDlg::OnEditClassName)
		CMD_CTRLMSG(IDC_GENERATE,	BN_CLICKED,		&AppDlg::OnGenerate)
		CMD_CTRLMSG(IDC_ABOUT,		BN_CLICKED,		&AppDlg::OnAbout)
	END_CTRLMSG_TABLE
}

////////////////////////////////////////////////////////////////////////////////
//! Handle dialog creation.

void AppDlg::OnInitDialog()
{
	if (g_app.m_templates.empty())
	{
		AlertMsg(TXT("There are no templates defined."));
		g_app.m_appWnd.Close();
		return;
	}

	if (g_app.m_components.empty())
	{
		AlertMsg(TXT("There are no components defined."));
		g_app.m_appWnd.Close();
		return;
	}

	// Load template names combo.
	for (size_t i = 0; i < g_app.m_templates.size(); ++i)
	{
		TemplatePtr templ = g_app.m_templates[i];
		tstring     item  = templ->m_name;

		m_cbTemplate.Add(item.c_str(), i);
	}

	// Select 1st template by default.
	m_cbTemplate.CurSel(m_cbTemplate.Find(g_app.m_templates[0]->m_name.c_str()));

	OnSelectTemplate();

	// Load component names combo.
	for (size_t i = 0; i < g_app.m_components.size(); ++i)
	{
		ComponentPtr component = g_app.m_components[i];
		tstring      item      = component->m_name;

		m_cbComponent.Add(item.c_str(), i);
	}

	// Make the last used component the default selection.
	size_t nComponent = m_cbComponent.Find(g_app.m_strLastComponent);

	// If none, pick the first component available.
	if ( (nComponent == Core::npos) && (!g_app.m_components.empty()) )
		nComponent = m_cbComponent.Find(g_app.m_components[0]->m_name.c_str());

	// Set selection, if possible.
	if (nComponent != Core::npos)
		m_cbComponent.CurSel(nComponent);

	OnSelectComponent();

	// Load last used folders combo.
	for (size_t i = 0; i < g_app.m_astrFolders.Size(); ++i)
		AddFolderName(tstring(g_app.m_astrFolders[i]), false);

	// Initialise with last settings.
	AddFolderName(tstring(g_app.m_strLastFolder), true);
}

////////////////////////////////////////////////////////////////////////////////
//! Handle dialog destruction.

void AppDlg::OnDestroy()
{
	// Use path as starting point for next selection.
	g_app.m_strLastComponent = m_cbComponent.Text();
	g_app.m_strLastFolder = m_cbFolder.Text();
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnClose()
{
	g_app.m_appWnd.Close();
}

////////////////////////////////////////////////////////////////////////////////
//! Handle the selection of a new component.

void AppDlg::OnSelectComponent()
{
	ASSERT(m_cbComponent.Count() > 0);

	// Get the selected component.
	int nSel  = m_cbComponent.CurSel();
	int nItem = m_cbComponent.ItemData(nSel);

	ComponentPtr pComponent = g_app.m_components[nItem];

	// Update controls.
	if (!pComponent->m_folder.empty())
		AddFolderName(pComponent->m_folder, true);

	m_namespaceEditor.Text(pComponent->m_namespace.c_str());
	m_componentLabel.Text(pComponent->m_description.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnSelectTemplate()
{
	ASSERT(m_cbTemplate.Count() > 0);

	// Get the selected template.
	int nSel  = m_cbTemplate.CurSel();
	int nItem = m_cbTemplate.ItemData(nSel);

	TemplatePtr pTemplate = g_app.m_templates[nItem];

	// Get fields expected.
	bool bIsClass = pTemplate->m_isClass;
	bool bHasHPP  = !pTemplate->m_headerFile.empty();
	bool bHasCPP  = !pTemplate->m_sourceFile.empty();

	// Update controls.
	m_templateLabel.Text(pTemplate->m_description.c_str());

	m_ebClassName.Enable(bIsClass);

	if (!bIsClass)
		m_ebClassName.Text(TXT(""));

	m_ebHPPFile.Enable(bHasHPP);

	if (!bHasHPP)
		m_ebHPPFile.Text(TXT(""));

	m_ebCPPFile.Enable(bHasCPP);

	if (!bHasCPP)
		m_ebCPPFile.Text(TXT(""));

	// Regenerate file names, if necessary.
	if (m_ebClassName.TextLength() > 0)
		OnEditClassName();
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnEditClassName()
{
	// Clear the filenames.
	if (m_ebClassName.TextLength() == 0)
	{
		m_ebHPPFile.Text(TXT(""));
		m_ebCPPFile.Text(TXT(""));
	}
	// Generate new filenames.
	else
	{
		CString strClassName = m_ebClassName.Text();

		if (m_ebHPPFile.IsEnabled())
			m_ebHPPFile.Text(strClassName + g_app.m_strHppExt);

		if (m_ebCPPFile.IsEnabled())
			m_ebCPPFile.Text(strClassName + g_app.m_strCppExt);
	}
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnBrowse()
{
	CPath strFolder = m_cbFolder.Text();

	// If folder name empty start from last path.
	if (strFolder == TXT(""))
		strFolder = g_app.m_strLastFolder;

	// Select the folder.
	if (!strFolder.SelectDir(*this, TXT("Select The Destination Folder"), strFolder))
		return;

	// Display path.
	AddFolderName(tstring(strFolder), true);
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::AddFolderName(const tstring& name, bool select)
{
	// Discard if empty.
	if (name.empty())
		return;

	// Already exists?
	size_t pos = m_cbFolder.FindExact(name.c_str());

	if (pos == Core::npos)
		pos = m_cbFolder.Add(name.c_str());

	// Make it selection?
	if (select)
		m_cbFolder.CurSel(pos);
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnGenerate()
{
	// Get the selected template.
	int nTemplSel  = m_cbTemplate.CurSel();
	int nTemplItem = m_cbTemplate.ItemData(nTemplSel);

	TemplatePtr pTemplate = g_app.m_templates[nTemplItem];

	// Get the selected template.
	int nComptSel  = m_cbComponent.CurSel();
	int nComptItem = m_cbComponent.ItemData(nComptSel);

	ComponentPtr pComponent = g_app.m_components[nComptItem];

	// Get expected fields.
	bool bIsClass = pTemplate->m_isClass;
	bool bHasHPP  = !pTemplate->m_headerFile.empty();
	bool bHasCPP  = !pTemplate->m_sourceFile.empty();

	// Validate class name.
	CString strClassName = m_ebClassName.Text();

	if (bIsClass && strClassName.Empty())
	{
		AlertMsg(TXT("You must supply a name for the class."));
		m_ebClassName.Focus();
		return;
	}

	// Validate folder.
	CPath strFolder = m_cbFolder.Text();

	if (!strFolder.Exists())
	{
		AlertMsg(TXT("The destination folder is invalid."));
		m_cbFolder.Focus();
		return;
	}

	// Validate HPP file name, if expected.
	CPath strHPPFile = m_ebHPPFile.Text();

	if (bHasHPP && strHPPFile.Empty())
	{
		AlertMsg(TXT("You must supply the HPP file name."));
		m_ebHPPFile.Focus();
		return;
	}

	// Validate CPP file name, if expected.
	CPath strCPPFile = m_ebCPPFile.Text();

	if (bHasCPP && strCPPFile.Empty())
	{
		AlertMsg(TXT("You must supply the CPP file name."));
		m_ebCPPFile.Focus();
		return;
	}

	Params params;

	params.add(TXT("Class"), tstring(strClassName));
	params.add(TXT("Component"), pComponent->m_name);
	params.add(TXT("Include"), pComponent->m_include);
	params.add(TXT("Comment"), pComponent->m_comment);
	params.add(TXT("Namespace"), tstring(m_namespaceEditor.Text()));
	params.add(TXT("Author"), g_app.m_author);

	// Generate HPP file, if required.
	if (!pTemplate->m_headerFile.empty())
	{
		CPath   strTemplateFile = CPath(g_app.m_strTmplFolder, pTemplate->m_headerFile.c_str());
		CString strFileTitle    = strHPPFile.FileTitle();
		CString strFileExt      = strHPPFile.FileExt();

		if (!strFileExt.Empty())
			strFileExt.Delete(0);

		params.add(TXT("File.Ext"), tstring(strHPPFile));
		params.add(TXT("File"), tstring(strFileTitle));
		params.add(TXT("Ext"), tstring(strFileExt));
		params.add(TXT("HdrExt"), tstring(strFileExt));

		if (!g_app.m_appCmds.generateFile(strTemplateFile, CPath(strFolder, strHPPFile), params))
			return;
	}

	// Generate CPP file, if required.
	if (!pTemplate->m_sourceFile.empty())
	{
		CPath   strTemplateFile = CPath(g_app.m_strTmplFolder, pTemplate->m_sourceFile.c_str());
		CString strFileTitle    = strCPPFile.FileTitle();
		CString strFileExt      = strCPPFile.FileExt();

		if (!strFileExt.Empty())
			strFileExt.Delete(0);

		params.add(TXT("File.Ext"), tstring(strCPPFile));
		params.add(TXT("File"), tstring(strFileTitle));
		params.add(TXT("Ext"), tstring(strFileExt));

		if (!g_app.m_appCmds.generateFile(strTemplateFile, CPath(strFolder, strCPPFile), params))
			return;
	}

	// Add folder to MRU list.
	if (g_app.m_astrFolders.Find(strFolder, true) == -1)
		g_app.m_astrFolders.Add(strFolder);

	if (!strClassName.Empty())
		NotifyMsg(TXT("%s class generated."), strClassName);
	else
		NotifyMsg(TXT("%s file generated."), strHPPFile);
}

////////////////////////////////////////////////////////////////////////////////
//!

void AppDlg::OnAbout()
{
	AboutDlg aboutDlg;

	aboutDlg.RunModal(*this);
}
