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

////////////////////////////////////////////////////////////////////////////////
//!

class ${Class} : public CPropertyPage
{
public:
	//! Default constructor.
	${Class}();

	//! Destructor.
	~${Class}();
	
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

#endif // ${FILE}_${EXT}
