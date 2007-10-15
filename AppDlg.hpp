/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APPDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAppDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef APPDLG_HPP
#define APPDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/MainDlg.hpp>
#include <WCL/ComboBox.hpp>
#include <WCL/EditBox.hpp>
#include <WCL/Path.hpp>

// Forward declarations.
class CParams;

/******************************************************************************
** 
** This is the main application dialog.
**
*******************************************************************************
*/

class CAppDlg : public CMainDlg
{
public:
	//
	// Constructors/Destructor.
	//
	CAppDlg();
	
	//
	// Methods.
	//

	//
	// Members.
	//
	CComboBox	m_cbTemplate;
	CComboBox	m_cbComponent;
	CEditBox	m_ebClassName;
	CComboBox 	m_cbFolder;
	CEditBox	m_ebCPPFile;
	CEditBox	m_ebHPPFile;

protected:
	//
	// Message processors.
	//
	virtual void OnInitDialog();
	virtual void OnDestroy();

	void OnClose();
	void OnSelectTemplate();
	void OnBrowse();
	void OnEditClassName();
	void OnGenerate();
	void OnAbout();

	//
	// Internal methods.
	//
	void AddFolderName(const CString& strName, bool bSelect);
	bool GenerateFile(const CPath& strTemplateFile, const CPath& strTargetFile, const CParams& oParams);
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //APPDLG_HPP
