////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.hpp
//! \brief  The $CLASS$ class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef $LIB_$$FILE$_HPP
#define $LIB_$$FILE$_HPP

#if _MSC_VER > 1000
#pragma once
#endif

namespace $NAMESPACE$
{

////////////////////////////////////////////////////////////////////////////////
//!

template <typename T>
class $CLASS$
{
public:
	//! Default constructor.
	$CLASS$();

	//! Destructor.
	~$CLASS$();
	
private:
	//
	// Members.
	//
};

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

template <typename T>
inline $CLASS$<T>::$CLASS$()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

template <typename T>
inline $CLASS$<T>::~$CLASS$()
{
}

//namespace $NAMESPACE$
}

#endif // $LIB_$$FILE$_HPP
