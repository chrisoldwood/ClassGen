////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${COMPONENT}_${FILE}_${EXT}
#define ${COMPONENT}_${FILE}_${EXT}

#if _MSC_VER > 1000
#pragma once
#endif

namespace ${Namespace}
{

////////////////////////////////////////////////////////////////////////////////
//!

template <typename T>
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

template <typename T>
inline ${Class}<T>::${Class}()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline ${Class}<T>::~${Class}()
{
}

//namespace ${Namespace}
}

#endif // ${COMPONENT}_${FILE}_${EXT}
