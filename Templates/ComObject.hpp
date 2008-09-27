////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.hpp
//! \brief  The $CLASS$ class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef $LIB_$$FILE$_HPP
#define $LIB_$$FILE$_HPP

#include <COM/IDispatchImpl.hpp>

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! .

class $CLASS$ : public COM::ObjectBase<?>, COM::IDispatchImpl<?>
{
public:
	//! Default constructor.
	$CLASS$();

	//! Destructor.
	virtual ~$CLASS$();
	
	DEFINE_INTERFACE_TABLE(???)
		IMPLEMENT_INTERFACE(IID_???, ???)
		IMPLEMENT_INTERFACE(IID_IDispatch, ???)
	END_INTERFACE_TABLE()

	IMPLEMENT_IUNKNOWN()
	IMPLEMENT_IDISPATCH($CLASS$)

	//
	// ??? methods.
	//

private:
	//
	// Members.
	//
};

#endif // $LIB_$$FILE$_HPP
