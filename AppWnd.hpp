////////////////////////////////////////////////////////////////////////////////
//! \file   AppWnd.hpp
//! \brief  The AppWnd class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APPWND_HPP
#define APPWND_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/DlgFrame.hpp>
#include "AppDlg.hpp"

////////////////////////////////////////////////////////////////////////////////
//! The applications main window.

class AppWnd : public CDlgFrame
{
public:
	//! Default constructor.
	AppWnd();

	//! Destructor.
	virtual ~AppWnd();

	//
	// Members.
	//
	AppDlg	m_appDlg;

protected:
	//
	// Message processors.
	//

	//! Handle window creation.
	virtual void OnCreate(const CRect& clientRect);
};

#endif // APPWND_HPP
