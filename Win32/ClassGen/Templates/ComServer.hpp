////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${COMPONENT}_${FILE}_${EXT}
#define ${COMPONENT}_${FILE}_${EXT}

#include <COM/InprocServer.hpp>
#include <COM/ServerRegInfo.hpp>
#include "TypeLibrary_h.h"

////////////////////////////////////////////////////////////////////////////////
//! The COM server concrete class.

class ${Class} : public COM::InprocServer
{
public:
	//! Default constructor.
	${Class}();

	//! Destructor.
	virtual ~${Class}();
	
private:
	DEFINE_REGISTRATION_TABLE("???", LIBID_???, 1, 0)
		DEFINE_CLASS_REG_INFO(CLSID_???,   "???",   "1", COM::SINGLE_THREAD_APT)
	END_REGISTRATION_TABLE()

	DEFINE_CLASS_FACTORY_TABLE()
		DEFINE_CLASS(CLSID_???, ???, I???)
	END_CLASS_FACTORY_TABLE()
};

////////////////////////////////////////////////////////////////////////////////
// Global variables.

//! The component object.
extern ${Class} g_oDll;

#endif // ${COMPONENT}_${FILE}_${EXT}
