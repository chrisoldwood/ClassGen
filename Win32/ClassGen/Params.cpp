/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		PARAMS.CPP
** COMPONENT:	The Application.
** DESCRIPTION:	CParams class definition.
**
*******************************************************************************
*/

#include "Common.hpp"
#include "Params.hpp"

/******************************************************************************
** Method:		Constructor.
**
** Description:	.
**
** Parameters:	None.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

CParams::CParams()
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

CParams::~CParams()
{
}

/******************************************************************************
** Method:		Add()
**
** Description:	Adds a Key/Value pair to the collection.
**
** Parameters:	pszKey		The key name.
**				pszValue	The value.
**
** Returns:		Nothing.
**
*******************************************************************************
*/

void CParams::Set(const char* pszKey, const char* pszValue)
{
	int i = IndexOf(pszKey);

	// Replacing existing key/value?
	if (i != -1)
	{
		m_astrKeys.Delete(i);
		m_astrValues.Delete(i);
	}

	// Add new key/value.
	m_astrKeys.Add(pszKey);
	m_astrValues.Add(pszValue);
}

/******************************************************************************
** Method:		Find()
**
** Description:	Finds the value for the given key.
**
** Parameters:	pszKey	The key name.
**
** Returns:		The value or "" if not found.
**
*******************************************************************************
*/

CString CParams::Find(const char* pszKey) const
{
	int i = IndexOf(pszKey);

	return (i != -1) ? m_astrValues[i] : "";
}

/******************************************************************************
** Method:		IndexOf()
**
** Description:	Finds the index of the key.
**
** Parameters:	pszKey	The key name.
**
** Returns:		The index or -1 if not found.
**
*******************************************************************************
*/

int CParams::IndexOf(const char* pszKey) const
{
	ASSERT(m_astrKeys.Size() == m_astrValues.Size());

	// For all keys...
	for (int i = 0; i < m_astrKeys.Size(); ++i)
	{
		if (m_astrKeys[i] == pszKey)
			return i;
	}

	return -1;
}
