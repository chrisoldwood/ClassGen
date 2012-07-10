////////////////////////////////////////////////////////////////////////////////
//! \file   ${File.Ext}
//! \brief  The ${Class} class definition.
//! \author ${Author}

#include "${Include}"
#include "${Header}"

////////////////////////////////////////////////////////////////////////////////
//! Default constructor.

${Class}::${Class}()
	: CPropertyPage(IDD_)
{
	DEFINE_CTRL_TABLE
	END_CTRL_TABLE

	DEFINE_CTRLMSG_TABLE
	END_CTRLMSG_TABLE
}

////////////////////////////////////////////////////////////////////////////////
//! Page initialisation handler.

void ${Class}::OnInitDialog()
{
}

////////////////////////////////////////////////////////////////////////////////
//! Page validation handler.

bool ${Class}::OnValidate()
{
	return true;
}