////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.hpp
//! \brief  The $CLASS$ class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef $LIB_$$FILE$_HPP
#define $LIB_$$FILE$_HPP

#include <COM/InprocServer.hpp>
#include <COM/ServerRegInfo.hpp>
#include "TypeLibrary_h.h"

////////////////////////////////////////////////////////////////////////////////
//! The COM server concrete class.

class $CLASS$ : public COM::InprocServer
{
public:
	//! Default constructor.
	$CLASS$();

	//! Destructor.
	virtual ~$CLASS$();
	
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
extern $CLASS$ g_oDll;

#endif // $LIB_$$FILE$_HPP
