#include "node.h"
#include <QtMath>

// 包含位置和编号信息的节点
Node::Node( QPointF p, int no)
	: mHaveTurnRestrict(false)
{
	mCoor = p;
	mNo = no;
}

Node::Node( const Node & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
	mSceneCoor = node.mSceneCoor;
	mId = node.mId;
	mJunctionType = node.mJunctionType;
	mInScale = node.mInScale;
	mHaveTurnRestrict = node.mHaveTurnRestrict;
}

Node::Node()
	: mHaveTurnRestrict(false)
{

}

bool Node::operator==( const Node & node ) const
{
	return (this->mCoor==node.mCoor) && (this->mNo==node.mNo)
		&& (mSceneCoor==node.mSceneCoor) && (mId==node.mId)
		&& (mJunctionType==node.mJunctionType) && (mInScale==node.mInScale)
		&& (mHaveTurnRestrict==node.mHaveTurnRestrict);
}

Node & Node::operator=( const Node & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
	mSceneCoor = node.mSceneCoor;
	mId= node.mId;
	mJunctionType = node.mJunctionType;
	mInScale = node.mInScale;
	mJunctionType = node.mJunctionType;
	return *this;
}


Rect Node::border() const
{
	return Rect(mCoor.x(), mCoor.y(), 0, 0);
}

void Node::norm( qreal factor, QPointF c )
{
	mCoor = (mCoor-c)/factor;
}

QPointF Node::coor() const
{
	return mCoor;
}

int Node::no() const
{
	return mNo;
}

Node& Node::setCoor( QPointF coor )
{
	mCoor = coor;
	return *this;
}

Node& Node::setNo( int no )
{
	mNo = no;
	return *this;
}

QPointF Node::sceneCoor() const
{
	return mSceneCoor;
}

Node& Node::setSceneCoor( QPointF coor )
{
	mSceneCoor = coor;
	return *this;
}

Node& Node::setJunctionType( int type )
{
	mJunctionType = type;
	return *this;
}

Node& Node::setInScale( bool in )
{
	mInScale = in;
	return *this;
}

int Node::junctionType() const
{
	return mJunctionType;
}

bool Node::inScale() const
{
	return mInScale;
}

int Node::id() const
{
	return mId;
}

Node& Node::setId( int id )
{
	mId = id;
	return *this;
}

qreal Node::dis( Node* node ) const
{
	QLineF line(mCoor, node->mCoor);
	return line.length();
}

qreal Node::sceneDis( Node* node ) const
{
	QLineF line(mSceneCoor, node->mSceneCoor);
	return line.length();
}

bool Node::haveTurnRestrict() const
{
	return mHaveTurnRestrict;
}

Node& Node::setHaveTurnRestrict( bool restr )
{
	mHaveTurnRestrict = restr;
	return *this;
}

TrafficVolume* Node::trafficVolume() const
{
	return mVolume;
}

Node& Node::setTrafficVolume(TrafficVolume* volume)
{
	mVolume = volume;
	return *this;
}



qreal length( QPair<Node,Node> pair )
{
	QPointF p1 = pair.first.coor();
	QPointF p2 = pair.second.coor();
	QPointF delta = p1 - p2;
	return qSqrt(qPow(delta.x(),2)+qPow(delta.y(),2));

}



