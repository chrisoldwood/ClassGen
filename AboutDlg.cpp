/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		ABOUTDLG.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CAboutDlg class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "AboutDlg.hpp"
#include "ClassGenApp.hpp"
#include <WCL/Path.hpp>
#include <WCL/VerInfoReader.hpp>

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

CAboutDlg::CAboutDlg()
	: CDialog(IDD_ABOUT)
{
	DEFINE_CTRL_TABLE
		CTRL(IDC_VERSION,	&m_txtVersion)
		CTRL(IDC_COPYRIGHT,	&m_txtCopyright)
		CTRL(IDC_EMAIL,		&m_txtEmail  )
		CTRL(IDC_WEBSITE,	&m_txtWebSite)
	END_CTRL_TABLE

	// Set the URL label protocols.
	m_txtEmail.Protocol(TXT("mailto:"));
	m_txtWebSite.Protocol(TXT("http://"));
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

void CAboutDlg::OnInitDialog()
{
	// Extract details from the resources.
	tstring strFileName  = CPath::Application();
	tstring strVersion   = WCL::VerInfoReader::GetStringValue(strFileName, WCL::VerInfoReader::PRODUCT_VERSION);
	tstring strCopyright = WCL::VerInfoReader::GetStringValue(strFileName, WCL::VerInfoReader::LEGAL_COPYRIGHT);

#ifdef _DEBUG
	strVersion += TXT(" [Debug]");
#endif

	// Update UI.
	m_txtVersion.Text(strVersion.c_str());
	m_txtCopyright.Text(strCopyright.c_str());
}
