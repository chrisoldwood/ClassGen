////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.cpp
//! \brief  The $CLASS$ class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "$File$.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

$CLASS$::$CLASS$()
	: CPropertySheet()
//	, m_oPage()
{
	// Set the title.
	m_strTitle = "Property Sheet";

	DEFINE_PAGE_TABLE
//		PAGE(&m_oPage,  "Page")
	END_PAGE_TABLE
}
