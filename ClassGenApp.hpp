/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		CLASSGENAPP.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	The CClassGenApp class declaration.
**
*******************************************************************************
*/

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
typedef std::vector<CTemplatePtr>  CTemplates;
typedef std::vector<CComponentPtr> CComponents;

/******************************************************************************
** 
** The application class.
**
*******************************************************************************
*/

class CClassGenApp : public CApp
{
public:
	//
	// Constructors/Destructor.
	//
	CClassGenApp();
	~CClassGenApp();

	//
	// Members
	//
	CAppWnd		m_AppWnd;			// Main window.
	CAppCmds	m_AppCmds;			// Command handler.

	CPath		m_strTmplFolder;	// Templates folder.
	CTemplates	m_aoTemplates;		// Templates collection.
	CComponents m_aoComponents;		// Components collection.
	CStrArray	m_astrFolders;		// List of folders used.
	CPath		m_strLastFolder;	// Last folder used.

	//
	// Constants.
	//
	static const tchar* VERSION;

protected:
	//
	// Startup and Shutdown template methods.
	//
	virtual	bool OnOpen();
	virtual	bool OnClose();

	//
	// Preferences.
	//
	CIniFile	m_oIniFile;		// .INI FIle

	//
	// Internal methods.
	//
	void LoadConfig();
	void SaveConfig();

	//
	// Constants.
	//
	static const tchar* INI_FILE_VER;
};

/******************************************************************************
**
** Global variables.
**
*******************************************************************************
*/

// The application object.
extern CClassGenApp App;

/******************************************************************************
**
** Implementation of inline functions.
**
*******************************************************************************
*/


#endif //CLASSGENAPP_HPP
