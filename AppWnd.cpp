/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APPWND.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAppWnd class definition.
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

CAppWnd::CAppWnd()
	: CDlgFrame(IDR_APPICON, m_AppDlg, true)
{
}

/******************************************************************************
** Method:		Destructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CAppWnd::~CAppWnd()
{
}

/******************************************************************************
** Method:		OnCreate()
**
** Description:	Creates the toolbar and status bars.
**
** Parameters:	rcClient	The client rectangle.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CAppWnd::OnCreate(const CRect& rcClient)
{
	//
	// Create and attach the components.
	//
	m_AppDlg.RunModeless(*this);
	ActiveDlg(&m_AppDlg);

	// Call base class.
	CDlgFrame::OnCreate(rcClient);
}
