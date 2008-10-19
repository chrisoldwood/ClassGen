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
	
	//
	// Members.
	//
	CComboBox	m_cbTemplate;
	CComboBox	m_cbComponent;
	CEditBox	m_ebClassName;
	CComboBox 	m_cbFolder;
	CEditBox	m_ebCPPFile;
	CEditBox	m_ebHPPFile;
	CEditBox	m_namespaceEditor;
	CLabel		m_componentLabel;
	CLabel		m_templateLabel;

protected:
	//
	// Message processors.
	//

	//! Handle dialog creation.
	virtual void OnInitDialog();

	//! Handle dialog destruction.
	virtual void OnDestroy();

	void OnClose();
	void OnSelectComponent();
	void OnSelectTemplate();
	void OnBrowse();
	void OnEditClassName();
	void OnGenerate();
	void OnAbout();

	//
	// Internal methods.
	//
	void AddFolderName(const tstring& name, bool select);
};

#endif // APPDLG_HPP
