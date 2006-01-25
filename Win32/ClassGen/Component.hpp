/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		COMPONENT.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CComponent class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

/******************************************************************************
** 
** Data class used to store the components details.
**
*******************************************************************************
*/

class CComponent
{
public:
	//
	// Members.
	//
	CString	m_strName;			// Component name.
	CString	m_strInclude;		// Header file to #include for PCH.
	CString	m_strComment;		// Comment for module banner.
	CString	m_strNamespace;		// Namespace for class.
};

// Smart pointer type.
typedef Core::SharedPtr<CComponent> CComponentPtr;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //COMPONENT_HPP
