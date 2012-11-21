////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class declaration.
//! \author ${Author}

// Check for previous inclusion
#ifndef ${COMPONENT}_${FILE}_${EXT}
#define ${COMPONENT}_${FILE}_${EXT}

#if _MSC_VER > 1000
#pragma once
#endif

#include <WCL/UiCommandBase.hpp>

////////////////////////////////////////////////////////////////////////////////
//! .

class ${Class} : public WCL::UiCommandBase
{
public:
	//! Constructor.
	${Class}();

	//
	// IUiCommand methods.
	//

	//! Execute the command.
	virtual void execute();

private:
	//
	// Members.
	//
};

#endif // ${COMPONENT}_${FILE}_${EXT}
