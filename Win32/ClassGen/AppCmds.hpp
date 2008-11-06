////////////////////////////////////////////////////////////////////////////////
//! \file   AppCmds.hpp
//! \brief  The AppCmds class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef APPCMDS_HPP
#define APPCMDS_HPP

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CmdCtrl.hpp>
#include <WCL/Path.hpp>

// Forward declarations.
class Params;

////////////////////////////////////////////////////////////////////////////////
//! Application command controller.

class AppCmds : public CCmdControl
{
public:
	//! Default constructor.
	AppCmds();

	//! Destructor.
	virtual ~AppCmds();

	//
	// Methods.
	//

	//! Generate the source file from the template.
	bool generateFile(const CPath& templateFile, CPath& targetFile, const Params& params);
};

#endif // APPCMDS_HPP
