////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class definition.
//! \author ${Author}

#include "${Include}"
#include "${Header}"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

${Class}::${Class}()
	: CPropertySheet()
//	, m_oPage()
{
	// Set the title.
	m_strTitle = "Property Sheet";

	DEFINE_PAGE_TABLE
//		PAGE(&m_oPage,  "Page")
	END_PAGE_TABLE
}
