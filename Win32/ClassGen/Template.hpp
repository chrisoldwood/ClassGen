/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		TEMPLATE.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CTemplate class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

/******************************************************************************
** 
** Data class used to store the templates details.
**
*******************************************************************************
*/

class CTemplate
{
public:
	//
	// Members.
	//
	CString	m_strName;
	CString	m_strHPPFile;
	CString	m_strCPPFile;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //TEMPLATE_HPP
