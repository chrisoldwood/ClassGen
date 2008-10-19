////////////////////////////////////////////////////////////////////////////////
//! \file   ClassGenApp.hpp
//! \brief  The ClassGenApp class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef CLASSGENAPP_HPP
#define CLASSGENAPP_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/App.hpp>
#include <WCL/IniFile.hpp>
#include <WCL/StrArray.hpp>
#include "Template.hpp"
#include "Component.hpp"
#include "AppWnd.hpp"
#include "AppCmds.hpp"

// Template shorthands.
typedef std::vector<TemplatePtr>  Templates;
typedef std::vector<ComponentPtr> Components;

////////////////////////////////////////////////////////////////////////////////
//! The application class.

class CClassGenApp : public CApp
{
public:
	//! Default constructor
	CClassGenApp();

	//! Destructor
	~CClassGenApp();

	//
	// Members
	//
	AppWnd		m_appWnd;			//!< The main window.
	AppCmds		m_appCmds;			//!< The command handler.

	CPath		m_strTmplFolder;	// Templates folder.
	Templates	m_templates;		//!< The templates collection.
	Components  m_components;		//!< The components collection.
	CStrArray	m_astrFolders;		// List of folders used.
	CString		m_strLastComponent;	// Last component used.
	CPath		m_strLastFolder;	// Last folder used.
	CString		m_strHppExt;		//!< The default extension for header files.
	CString		m_strCppExt;		//!< The default extension for source files.
	tstring		m_author;			//!< The name of the class Author.

protected:
	//
	// CApp overriden methods.
	//

	//! Handle application startup.
	virtual	bool OnOpen();

	//! Handle application shutdown.
	virtual	bool OnClose();

	//
	// Internal methods.
	//

	//! Load the application settings.
	void loadConfig();

	//! Save the application settings.
	void saveConfig();
};

////////////////////////////////////////////////////////////////////////////////
// Global variables.

//! The application object.
extern CClassGenApp g_app;

#endif // CLASSGENAPP_HPP
