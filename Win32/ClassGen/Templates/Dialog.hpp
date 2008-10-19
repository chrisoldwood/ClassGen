////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${FILE}_${EXT}
#define ${FILE}_${EXT}

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/CommonUI.hpp>

////////////////////////////////////////////////////////////////////////////////
//!

class ${Class} : public CDialog
{
public:
	//! Default constructor.
	${Class}();
	
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

	//! Dialog initialisation handler.
	virtual void OnInitDialog();

	//! OK button handler.
	virtual bool OnOk();
};

#endif // ${FILE}_${EXT}
