////////////////////////////////////////////////////////////////////////////////
//! \file   Params.cpp
//! \brief  The Params class definition.
//! \author Chris Oldwood

#include "Common.hpp"
#include "Params.hpp"
#include <Core/StringUtils.hpp>

////////////////////////////////////////////////////////////////////////////////
//! Default constructor

Params::Params()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Destructor.

Params::~Params()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Add a key value pair. This also adds an all uppercase and all lowercase
//! version as well.

void Params::add(const tstring& key, const tstring& value)
{
	m_params[key] = value;
	m_params[Core::createUpper(key)] = Core::createUpper(value);
	m_params[Core::createLower(key)] = Core::createLower(value);
}

////////////////////////////////////////////////////////////////////////////////
//! Check if a key exists.

bool Params::exists(const tstring& key) const
{
	return (m_params.find(key) != m_params.end());
}

////////////////////////////////////////////////////////////////////////////////
//! Find the value for key.

tstring Params::find(const tstring& key) const
{
	tstring value;

	KeyValueMap::const_iterator it = m_params.find(key);

	if (it != m_params.end())
		value = it->second;

	return value;
}
