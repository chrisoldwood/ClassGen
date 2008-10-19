////////////////////////////////////////////////////////////////////////////////
//! \file   Component.hpp
//! \brief  The Component struct declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! Data class used to store the components details.

struct Component
{
	tstring	m_name;			//!< The component name.
	tstring	m_description;	//!< The component description.
	tstring	m_include;		//!< Header file to #include for PCH.
	tstring	m_comment;		//!< Comment for module banner.
	tstring	m_namespace;	//!< Namespace for class.
	tstring	m_folder;		//!< The compnents folder.
};

//! The default Component smart-pointer type.
typedef Core::SharedPtr<Component> ComponentPtr;

#endif // COMPONENT_HPP
