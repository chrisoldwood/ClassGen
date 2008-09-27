////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.cpp
//! \brief  The $CLASS$ class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "$File$.hpp"

////////////////////////////////////////////////////////////////////////////////
//! Constructor for a specific database. Create the table ready for inclusion
//! in the memory database provided.

$CLASS$::$CLASS$(CMDB& oDB)
	: CTable(oDB, "")
{
	// Create the table schema.
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

$CLASS$::~$CLASS$()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Create a row for the table. Allocates a row and initialises any fields with
//! default values.

CRow& $CLASS$::CreateRow()
{
	CRow& oRow = CTable::CreateRow();

//	oRow[ID] = ;
	
	return oRow;
}