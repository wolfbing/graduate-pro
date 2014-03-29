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
	node1 = n1;
	node2 = n2;
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

ConnWithCoorPair::ConnWithCoorPair( const ConnWithCoorPair & conn )
{
	mCoorPair = conn.mCoorPair;
}

bool ConnWithCoorPair::operator==(const ConnWithCoorPair & conn ) const
{
	return (this->mCoorPair.first==conn.mCoorPair.first)
		&& (this->mCoorPair.second==conn.mCoorPair.second);
}

ConnWithCoorPair & ConnWithCoorPair::operator=( const ConnWithCoorPair & conn )
{
	mCoorPair = conn.mCoorPair;
	return *this;
}

Rect ConnWithCoorPair::border() const
{
	qreal left, right, top, bottom;
	if (mCoorPair.first.x()<mCoorPair.second.x())
	{
		left = mCoorPair.first.x();
		right = mCoorPair.second.x();
	}
	else
	{
		left = mCoorPair.second.x();
		right = mCoorPair.first.x();
	}
	if (mCoorPair.first.y()>mCoorPair.second.y())
	{
		top = mCoorPair.first.y();
		bottom = mCoorPair.second.y();
	}
	else
	{
		top = mCoorPair.second.y();
		bottom = mCoorPair.first.y();
	}
	return Rect(left, top, right-left, top-bottom);
	 
}

void ConnWithCoorPair::norm( qreal factor, QPointF c )
{
	mCoorPair = QPair<QPointF, QPointF>((mCoorPair.first-c)/factor,(mCoorPair.second-c)/factor );
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
