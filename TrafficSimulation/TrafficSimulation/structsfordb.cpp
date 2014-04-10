
#include "structsfordb.h"


///////////  TreeInt   /////////////////


TreeInt::TreeInt( int i1,int i2,int i3 )
{
	m3 = i3;
	m2 = i2;
	m1 = i1;
}

TreeInt::TreeInt( const TreeInt & obj )
{
	m1 = obj.m1;
	m2 = obj.m2;
	m3 = obj.m3;
}

TreeInt& TreeInt::operator=( const TreeInt & obj )
{
	m1 = obj.m1;
	m2 = obj.m2;
	m3 = obj.m3;
	return *this;
}

bool TreeInt::operator==( const TreeInt & obj) const
{
	return m1==obj.m1
		&& m2==obj.m2
		&& m3==obj.m3;

}


///////  TreeInt  End   ///////////////////




TwoInt& TwoInt::operator=( const TwoInt & obj )
{
	m1 = obj.m1;
	m2 = obj.m2;
	return *this;
}

bool TwoInt::operator==( const TwoInt & obj ) const
{
	return m1==obj.m1 && m2==obj.m2;
}
