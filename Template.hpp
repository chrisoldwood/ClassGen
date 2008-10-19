////////////////////////////////////////////////////////////////////////////////
//! \file   Template.hpp
//! \brief  The Template struct declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//! Data class used to store the templates details.

struct Template
{
	tstring	m_name;			//!< The template name.
	tstring	m_description;	//!< The template description.
	bool	m_isClass;		//!< Is a class template?
	tstring	m_headerFile;	//!< The template .HPP file.
	tstring	m_sourceFile;	//!< The template .CPP file.
};

//! The default Template smart-pointer type.
typedef Core::SharedPtr<Template> TemplatePtr;

#endif // TEMPLATE_HPP
