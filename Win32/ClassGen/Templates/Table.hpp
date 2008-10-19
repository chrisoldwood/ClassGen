////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${FILE}_${EXT}
#define ${FILE}_${EXT}

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//!

class ${Class} : public CTable
{
public:
	//! Constructor for a specific database.
	${Class}(CMDB& oDB);

	//! Destructor.
	~${Class}();
	
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

#endif // ${FILE}_${EXT}
