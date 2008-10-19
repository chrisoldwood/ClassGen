////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${COMPONENT}_${FILE}_${EXT}
#define ${COMPONENT}_${FILE}_${EXT}

#include <COM/IDispatchImpl.hpp>

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! .

class ${Class} : public COM::ObjectBase<?>, COM::IDispatchImpl<?>
{
public:
	//! Default constructor.
	${Class}();

	//! Destructor.
	virtual ~${Class}();
	
	DEFINE_INTERFACE_TABLE(???)
		IMPLEMENT_INTERFACE(IID_???, ???)
		IMPLEMENT_INTERFACE(IID_IDispatch, ???)
	END_INTERFACE_TABLE()

	IMPLEMENT_IUNKNOWN()
	IMPLEMENT_IDISPATCH(${Class})

	//
	// ??? methods.
	//

private:
	//
	// Members.
	//
};

#endif // ${COMPONENT}_${FILE}_${EXT}
