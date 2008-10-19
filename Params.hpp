////////////////////////////////////////////////////////////////////////////////
//! \file   Params.hpp
//! \brief  The Params class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef PARAMS_HPP
#define PARAMS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! Collection class used to hold the string substitutions.

class Params
{
public:
	//! Default constructor
	Params();

	//! Destructor.
	~Params();

	//
	// Methods.
	//

	//! Add a key value pair.
	void add(const tstring& key, const tstring& value);

	//! Check if a key exists.
	bool exists(const tstring& key) const;

	//! Find the value for key.
	tstring find(const tstring& key) const;

protected:
	//! The underlying collection type.
	typedef std::map<tstring, tstring> KeyValueMap;

	//
	// Members.
	//
	KeyValueMap	m_params;	//! The underlying collection.
};

#endif // PARAMS_HPP
