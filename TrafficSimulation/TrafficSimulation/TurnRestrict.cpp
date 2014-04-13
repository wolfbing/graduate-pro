#include "TurnRestrict.h"


TurnRestrict::TurnRestrict(void)
{
}


TurnRestrict::~TurnRestrict(void)
{
}

TurnRestrict & TurnRestrict::setCurrentNodeNo( int no )
{
	mCurrentNodeNo = no;
	return *this;
}

TurnRestrict & TurnRestrict::setFromNodeNo( int no )
{
	mFromNodeNo = no;
	return *this;
}

TurnRestrict & TurnRestrict::setToNodeNo( int no )
{
	mToNodeNo = no;
	return *this;
}

int TurnRestrict::currentNodeNo()
{
	return mCurrentNodeNo;
}

int TurnRestrict::fromNodeNo()
{
	return mFromNodeNo;
}

int TurnRestrict::toNodeNo()
{
	return mToNodeNo;
}
