/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ABOUTDLG.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CAboutDlg class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef ABOUTDLG_HPP
#define ABOUTDLG_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

/******************************************************************************
** 
** This is the dialog that display program version and copyright information.
**
*******************************************************************************
*/

class CAboutDlg : public CDialog
{
public:
	//
	// Constructors/Destructor.
	//
	CAboutDlg();
	
protected:
	//
	// Members.
	//
	CLabel		m_txtVersion;		//!< The version label.
	CLabel		m_txtCopyright;		//!< The copyright label.
	CURLLabel	m_txtEmail;			//!< The email address label.
	CURLLabel	m_txtWebSite;		//!< The website label.
	
	//
	// Message processors.
	//
	virtual void OnInitDialog();
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //ABOUTDLG_HPP
