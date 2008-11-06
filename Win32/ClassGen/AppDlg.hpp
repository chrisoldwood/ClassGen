////////////////////////////////////////////////////////////////////////////////
//! \file   AppDlg.hpp
//! \brief  The AppDlg class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APPDLG_HPP
#define APPDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/MainDlg.hpp>
#include <WCL/ComboBox.hpp>
#include <WCL/EditBox.hpp>
#include <WCL/Label.hpp>
#include <WCL/Path.hpp>

////////////////////////////////////////////////////////////////////////////////
//! The application main dialog.

class AppDlg : public CMainDlg
{
public:
	//! Default constructor.
	AppDlg();
	
private:
	//
	// Members.
	//
	CComboBox	m_templateList;
	CComboBox	m_componentList;
	CEditBox	m_classNameEditor;
	CComboBox 	m_folderList;
	CEditBox	m_cppFileEditor;
	CEditBox	m_hppFileEditor;
	CEditBox	m_namespaceEditor;
	CLabel		m_componentLabel;
	CLabel		m_templateLabel;

	//
	// Message processors.
	//

	//! Handle dialog creation.
	virtual void OnInitDialog();

	//! Handle dialog destruction.
	virtual void OnDestroy();

	//! Handle the close button being pressed.
	void onClose();

	//! Handle the selection of a new component.
	void onSelectComponent();

	//! Handle the selection of a new template.
	void onSelectTemplate();

	//! Show the common dialog to select a folder.
	void onBrowse();

	//! Handle a change to the class name.
	void onEditClassName();

	//! Generate the new class.
	void onGenerate();

	//! Show the HelpFile.
	void onHelp();

	//! Show the application version.
	void onAbout();

	//
	// Internal methods.
	//

	//! Add a folder to the folder MRU list.
	void addFolderName(const tstring& name, bool select);
};

#endif // APPDLG_HPP
