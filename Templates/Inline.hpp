////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${LIB}_${FILE}_${EXT}
#define ${LIB}_${FILE}_${EXT}

#if _MSC_VER > 1000
#pragma once
#endif

namespace ${Namespace}
{

////////////////////////////////////////////////////////////////////////////////
//!

class ${Class}
{
public:
	//! Default constructor.
	${Class}();

	//! Destructor.
	~${Class}();
	
private:
	//
	// Members.
	//
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

inline ${Class}::${Class}()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

inline ${Class}::~${Class}()
{
}

//namespace ${Namespace}
}

#endif // ${LIB}_${FILE}_${EXT}
