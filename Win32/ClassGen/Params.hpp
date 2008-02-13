/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PARAMS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CParams class declaration.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef PARAMS_HPP
#define PARAMS_HPP

#include <WCL/StrArray.hpp>

/******************************************************************************
** 
** Collection class used to hold the string substitution table.
**
*******************************************************************************
*/

class CParams
{
public:
	//
	// Constructors/Destructor.
	//
	CParams();
	~CParams();

	//
	// Methods.
	//
	void    Set(const tchar* pszKey, const tchar* pszValue);

	CString Find(const tchar* pszKey) const;

protected:
	//
	// Members.
	//
	CStrArray	m_astrKeys;
	CStrArray	m_astrValues;

	//
	// Internal methods.
	//
	int IndexOf(const tchar* pszKey) const;
};

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/

#endif //PARAMS_HPP
