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
	CString	m_strName;			// The template name.
	bool	m_bNeedsClass;		// Is a class template?
	CString	m_strHPPFile;		// The template .HPP file.
	CString	m_strCPPFile;		// The template .CPP file.
};

// Smart pointer type.
typedef Core::SharedPtr<CTemplate> CTemplatePtr;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //TEMPLATE_HPP
