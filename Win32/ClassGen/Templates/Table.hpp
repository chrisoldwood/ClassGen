////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.hpp
//! \brief  The $CLASS$ class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef $FILE$_HPP
#define $FILE$_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//!

class $CLASS$ : public CTable
{
public:
	//! Constructor for a specific database.
	$CLASS$(CMDB& oDB);

	//! Destructor.
	~$CLASS$();
	
	//
	// Column indices.
	//
	enum
	{
		ID,

		NUM_COLUMNS,
	};

	//
	// Column lengths.
	//
	enum
	{
	};

	//
	// Methods.
	//

	//! Create a row for the table.
	virtual CRow& CreateRow();
};

#endif // $FILE$_HPP
