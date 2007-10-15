/******************************************************************************
** (C) Chris Oldwood
**
** MODULE:		APPHEADERS.HPP
** COMPONENT:	The Application.
** DESCRIPTION:	Wrapper to include all the main application headers.
**
*******************************************************************************
*/

// Check for previous inclusion
#ifndef APPHEADERS_HPP
#define APPHEADERS_HPP

/******************************************************************************
**
** System headers.
**
*******************************************************************************
*/

#include <Core/Common.hpp>		// Core library common headers.
#include <WCL/wcl.hpp>			// Windows C++ library.

/******************************************************************************
**
** Application specific headers.
**
*******************************************************************************
*/

#include "Resource.h"

// App data classes.
#include "Template.hpp"
#include "Component.hpp"
#include "Params.hpp"

// App GUI classes.
#include "AppCmds.hpp"
#include "AppToolBar.hpp"
#include "AppDlg.hpp"
#include "AppWnd.hpp"
#include "ClassGenApp.hpp"

#endif //APPHEADERS_HPP
