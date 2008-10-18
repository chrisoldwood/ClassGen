////////////////////////////////////////////////////////////////////////////////
//! \file   $File$.hpp
//! \brief  The $CLASS$ class declaration.
//! \author Chris Oldwood

// Check for previous inclusion
#ifndef $FILE$_HPP
#define $FILE$_HPP

#if _MSC_VER > 1000
#pragma once
#endif

////////////////////////////////////////////////////////////////////////////////
//!

class $CLASS$ : public CPropertyPage
{
public:
	//! Default constructor.
	$CLASS$();

	//! Destructor.
	~$CLASS$();
	
	//
	// Members.
	//
	
private:
	//
	// Members.
	//
	
	//
	// Controls.
	//

	//
	// Message handlers.
	//

	//! Page initialisation handler.
	virtual void OnInitDialog();

	//! Page validation handler.
	virtual bool OnValidate();
};

#endif // $FILE$_HPP