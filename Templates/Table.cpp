////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class definition.
//! \author ${Author}

#include "${Include}"
#include "${File}.${HdrExt}"

////////////////////////////////////////////////////////////////////////////////
//! Constructor for a specific database. Create the table ready for inclusion
//! in the memory database provided.

${Class}::${Class}(CMDB& oDB)
	: CTable(oDB, "")
{
	// Create the table schema.
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

${Class}::~${Class}()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Create a row for the table. Allocates a row and initialises any fields with
//! default values.

CRow& ${Class}::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID] = ;
	
	return oRow;
}
