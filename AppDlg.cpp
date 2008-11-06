////////////////////////////////////////////////////////////////////////////////
//! \file   AppDlg.cpp
//! \brief  The AppDlg class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "AppDlg.hpp"
#include "AboutDlg.hpp"
#include "ClassGenApp.hpp"
#include "Params.hpp"
#include <WCL/BusyCursor.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

AppDlg::AppDlg()
	: CMainDlg(IDD_MAIN)
{

	DEFINE_CTRL_TABLE
		CTRL(IDC_TEMPLATE,		&m_templateList)
		CTRL(IDC_COMPONENT,		&m_componentList)
		CTRL(IDC_CLASS_NAME,	&m_classNameEditor)
		CTRL(IDC_FOLDER,		&m_folderList)
		CTRL(IDC_HPP_FILE,		&m_hppFileEditor)
		CTRL(IDC_CPP_FILE,		&m_cppFileEditor)
		CTRL(IDC_NAMESPACE,		&m_namespaceEditor)
		CTRL(IDC_COMP_DESC,		&m_componentLabel)
		CTRL(IDC_TMPL_DESC,		&m_templateLabel)
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
		CMD_CTRLMSG(IDC_COMPONENT,	CBN_SELCHANGE,	&AppDlg::onSelectComponent)
		CMD_CTRLMSG(IDC_TEMPLATE,	CBN_SELCHANGE,	&AppDlg::onSelectTemplate)
		CMD_CTRLMSG(IDC_CLOSE,		BN_CLICKED,		&AppDlg::onClose)
		CMD_CTRLMSG(IDC_BROWSE,		BN_CLICKED,		&AppDlg::onBrowse)
		CMD_CTRLMSG(IDC_CLASS_NAME,	EN_CHANGE,		&AppDlg::onEditClassName)
		CMD_CTRLMSG(IDC_GENERATE,	BN_CLICKED,		&AppDlg::onGenerate)
		CMD_CTRLMSG(IDC_MANUAL,		BN_CLICKED,		&AppDlg::onHelp)
		CMD_CTRLMSG(IDC_ABOUT,		BN_CLICKED,		&AppDlg::onAbout)
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

		m_templateList.Add(item.c_str(), i);
	}

	// Select 1st template by default.
	m_templateList.CurSel(m_templateList.Find(g_app.m_templates[0]->m_name.c_str()));

	onSelectTemplate();

	// Load component names combo.
	for (size_t i = 0; i < g_app.m_components.size(); ++i)
	{
		ComponentPtr component = g_app.m_components[i];
		tstring      item      = component->m_name;

		m_componentList.Add(item.c_str(), i);
	}

	// Make the last used component the default selection.
	size_t component = m_componentList.Find(g_app.m_lastComponent);

	// If none, pick the first component available.
	if ( (component == Core::npos) && (!g_app.m_components.empty()) )
		component = m_componentList.Find(g_app.m_components[0]->m_name.c_str());

	// Set selection, if possible.
	if (component != Core::npos)
		m_componentList.CurSel(component);

	onSelectComponent();

	// Load last used folders combo.
	for (size_t i = 0; i < g_app.m_mruFolders.Size(); ++i)
		addFolderName(tstring(g_app.m_mruFolders[i]), false);

	// Initialise with last settings.
	addFolderName(tstring(g_app.m_lastFolder), true);
}

////////////////////////////////////////////////////////////////////////////////
//! Handle dialog destruction.

void AppDlg::OnDestroy()
{
	// Use path as starting point for next selection.
	g_app.m_lastComponent = m_componentList.Text();
	g_app.m_lastFolder = m_folderList.Text();
}

////////////////////////////////////////////////////////////////////////////////
//! Handle the close button being pressed.

void AppDlg::onClose()
{
	g_app.m_appWnd.Close();
}

////////////////////////////////////////////////////////////////////////////////
//! Handle the selection of a new component.

void AppDlg::onSelectComponent()
{
	ASSERT(m_componentList.Count() > 0);

	// Get the selected component.
	size_t sel  = m_componentList.CurSel();
	size_t item = m_componentList.ItemData(sel);

	ComponentPtr pComponent = g_app.m_components[item];

	// Update controls.
	if (!pComponent->m_folder.empty())
		addFolderName(pComponent->m_folder, true);

	m_namespaceEditor.Text(pComponent->m_namespace.c_str());
	m_componentLabel.Text(pComponent->m_description.c_str());
}

////////////////////////////////////////////////////////////////////////////////
//! Handle the selection of a new template.

void AppDlg::onSelectTemplate()
{
	ASSERT(m_templateList.Count() > 0);

	// Get the selected template.
	size_t sel  = m_templateList.CurSel();
	size_t item = m_templateList.ItemData(sel);

	TemplatePtr pTemplate = g_app.m_templates[item];

	// Get fields expected.
	bool isClass = pTemplate->m_isClass;
	bool hasHPP  = !pTemplate->m_headerFile.empty();
	bool hasCPP  = !pTemplate->m_sourceFile.empty();

	// Update controls.
	m_templateLabel.Text(pTemplate->m_description.c_str());

	m_classNameEditor.Enable(isClass);

	if (!isClass)
		m_classNameEditor.Text(TXT(""));

	m_hppFileEditor.Enable(hasHPP);

	if (!hasHPP)
		m_hppFileEditor.Text(TXT(""));

	m_cppFileEditor.Enable(hasCPP);

	if (!hasCPP)
		m_cppFileEditor.Text(TXT(""));

	// Regenerate file names, if necessary.
	if (m_classNameEditor.TextLength() > 0)
		onEditClassName();
}

////////////////////////////////////////////////////////////////////////////////
//! Handle a change to the class name.

void AppDlg::onEditClassName()
{
	// Clear the filenames.
	if (m_classNameEditor.TextLength() == 0)
	{
		m_hppFileEditor.Text(TXT(""));
		m_cppFileEditor.Text(TXT(""));
	}
	// Generate new filenames.
	else
	{
		CString className = m_classNameEditor.Text();

		if (m_hppFileEditor.IsEnabled())
			m_hppFileEditor.Text(className + g_app.m_headerExt);

		if (m_cppFileEditor.IsEnabled())
			m_cppFileEditor.Text(className + g_app.m_sourceExt);
	}
}

////////////////////////////////////////////////////////////////////////////////
//! Show the common dialog to select a folder.

void AppDlg::onBrowse()
{
	CPath folder = m_folderList.Text();

	// If folder name empty start from last path.
	if (folder == TXT(""))
		folder = g_app.m_lastFolder;

	// Select the folder.
	if (!folder.SelectDir(*this, TXT("Select The Destination Folder"), folder))
		return;

	// Display path.
	addFolderName(tstring(folder), true);
}

////////////////////////////////////////////////////////////////////////////////
//! Add a folder to the folder MRU list. This ensures that duplicates are not
//! added and can set it as the current selection.

void AppDlg::addFolderName(const tstring& name, bool select)
{
	// Discard if empty.
	if (name.empty())
		return;

	// Already exists?
	size_t pos = m_folderList.FindExact(name.c_str());

	if (pos == Core::npos)
		pos = m_folderList.Add(name.c_str());

	// Make it selection?
	if (select)
		m_folderList.CurSel(pos);
}

////////////////////////////////////////////////////////////////////////////////
//! Generate the new class.

void AppDlg::onGenerate()
{
	// Get the selected template.
	int templSel  = m_templateList.CurSel();
	int templItem = m_templateList.ItemData(templSel);

	TemplatePtr templt = g_app.m_templates[templItem];

	// Get the selected template.
	int comptSel  = m_componentList.CurSel();
	int comptItem = m_componentList.ItemData(comptSel);

	ComponentPtr component = g_app.m_components[comptItem];

	// Get expected fields.
	bool isClass = templt->m_isClass;
	bool hasHpp  = !templt->m_headerFile.empty();
	bool hasCpp  = !templt->m_sourceFile.empty();

	// Validate class name.
	CString className = m_classNameEditor.Text();

	if (isClass && className.Empty())
	{
		AlertMsg(TXT("You must supply a name for the class."));
		m_classNameEditor.Focus();
		return;
	}

	// Validate folder.
	CPath folder = m_folderList.Text();

	if (!folder.Exists())
	{
		AlertMsg(TXT("The destination folder is invalid."));
		m_folderList.Focus();
		return;
	}

	// Validate HPP file name, if expected.
	CPath hppFile = m_hppFileEditor.Text();

	if (hasHpp && hppFile.Empty())
	{
		AlertMsg(TXT("You must supply the HPP file name."));
		m_hppFileEditor.Focus();
		return;
	}

	// Validate CPP file name, if expected.
	CPath cppFile = m_cppFileEditor.Text();

	if (hasCpp && cppFile.Empty())
	{
		AlertMsg(TXT("You must supply the CPP file name."));
		m_cppFileEditor.Focus();
		return;
	}

	Params params;

	params.add(TXT("Class"), tstring(className));
	params.add(TXT("Component"), component->m_name);
	params.add(TXT("Include"), component->m_include);
	params.add(TXT("Comment"), component->m_comment);
	params.add(TXT("Namespace"), tstring(m_namespaceEditor.Text()));
	params.add(TXT("Author"), g_app.m_author);

	// Generate HPP file, if required.
	if (!templt->m_headerFile.empty())
	{
		CPath   templateFile = CPath(g_app.m_templatesFolder, templt->m_headerFile.c_str());
		CString fileTitle    = hppFile.FileTitle();
		CString fileExt      = hppFile.FileExt();

		// Remove leading '.'.
		if (!fileExt.Empty())
			fileExt.Delete(0);

		params.add(TXT("File.Ext"), tstring(hppFile));
		params.add(TXT("File"), tstring(fileTitle));
		params.add(TXT("Ext"), tstring(fileExt));
		params.add(TXT("Header"), tstring(hppFile));

		CPath targetFile(folder, hppFile);

		if (!g_app.m_appCmds.generateFile(templateFile, targetFile, params))
			return;
	}

	// Generate CPP file, if required.
	if (!templt->m_sourceFile.empty())
	{
		CPath   templateFile = CPath(g_app.m_templatesFolder, templt->m_sourceFile.c_str());
		CString fileTitle    = cppFile.FileTitle();
		CString fileExt      = cppFile.FileExt();

		// Remove leading '.'.
		if (!fileExt.Empty())
			fileExt.Delete(0);

		params.add(TXT("File.Ext"), tstring(cppFile));
		params.add(TXT("File"), tstring(fileTitle));
		params.add(TXT("Ext"), tstring(fileExt));

		CPath targetFile(folder, cppFile);

		if (!g_app.m_appCmds.generateFile(templateFile, targetFile, params))
			return;
	}

	// Add folder to MRU list.
	if (g_app.m_mruFolders.Find(folder, true) == -1)
		g_app.m_mruFolders.Add(folder);

	if (!className.Empty())
		NotifyMsg(TXT("%s class generated."), className);
	else
		NotifyMsg(TXT("%s file generated."), hppFile);
}

////////////////////////////////////////////////////////////////////////////////
//! Show the HelpFile.

void AppDlg::onHelp()
{
	CBusyCursor busyCursor;

	::ShellExecute(NULL, NULL, CPath::ApplicationDir() / TXT("ClassGen.mht"), NULL, NULL, SW_SHOW);
}

////////////////////////////////////////////////////////////////////////////////
//! Show the application version.

void AppDlg::onAbout()
{
	AboutDlg aboutDlg;

	aboutDlg.RunModal(*this);
}
