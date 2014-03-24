#include "conn.h"

ConnWithCoorLevel::ConnWithCoorLevel(QPair<QPointF,QPointF> coor, int level)
	: mCoorPair(coor)
	, mRoadLevel(level)
{

}

void ConnWithCoorLevel::setConn( QPair<QPointF,QPointF> coor )
{
	mCoorPair = coor;
}

void ConnWithCoorLevel::setLevel( int level )
{
	mRoadLevel = level;
}

ConnWithNoPair::ConnWithNoPair( int n1,int n2 )
{
	if (n1 < n2)
	{
		node1 = n1;
		node2 = n2;
	}
	else
	{
		node1 = n2;
		node2 = n1;
	}
}

ConnWithNoPair::ConnWithNoPair( const ConnWithNoPair & conn )
{
	this->node1 = conn.node1;
	this->node2 = conn.node2;
}


bool ConnWithNoPair::operator==(const ConnWithNoPair & conn ) const
{
	return (this->node1==conn.node1)
		&& (this->node2==conn.node2);
}

ConnWithNoPair& ConnWithNoPair::operator=( const ConnWithNoPair & conn )
{
	this->node1 = conn.node1;
	this->node2 = conn.node2;
	return *this;
}

ConnWithCoorPair::ConnWithCoorPair( QPointF p1,QPointF p2 )
	: mCoorPair(QPair<QPointF,QPointF>(p1,p2))
{

}

bool ConnWithCoorPair::operator==(const ConnWithCoorPair & conn ) const
{
	return (this->mCoorPair.first==conn.mCoorPair.first)
		&& (this->mCoorPair.second==conn.mCoorPair.second);
}

QDataStream& operator<<( QDataStream& out, const ConnWithNoPair& conn )
{
	out<<conn.node1<<conn.node2;
	return out;
}

QDataStream& operator>>( QDataStream& in, ConnWithNoPair& conn )
{
	int n1,n2;
	in >>n1>>n2;
	conn.node1 = n1;
	conn.node2 = n2;
	return in;
}
