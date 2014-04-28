#include "Edge.h"




Edge::~Edge(void)
{
}

Edge::Edge( const Edge & edge)
{
	// 复制地址值而不是重新创造节点
	// 因为节点是边的依赖, 是独立的, 边没能力构造, 也不应该构造
	mDestNode = edge.mDestNode;
	mSourceNode = edge.mSourceNode;
	mRoadLevel = edge.mRoadLevel;
}

Edge& Edge::operator=( const Edge & edge )
{
	mDestNode = edge.mDestNode;
	mSourceNode = edge.mSourceNode;
	mRoadLevel = edge.mRoadLevel;
	return *this;
}

bool Edge::operator==( const Edge & edge )
{
	return mDestNode==edge.mDestNode
		&& mSourceNode==edge.mSourceNode
		&& mRoadLevel==edge.mRoadLevel
		;
}

Node * Edge::sourceNode() const
{
	return mSourceNode;
}

Node * Edge::destNode() const
{
	return mDestNode;
}

Edge & Edge::setSourceNode( Node * node)
{
	mSourceNode = node;
	return *this;
}

Edge & Edge::setDestNode( Node * node)
{
	mDestNode = node;
	return *this;
}

Edge & Edge::setRoadLevel( uint level )
{
	mRoadLevel = level;
	return *this;
}

uint Edge::roadLevel() const
{
	return mRoadLevel;
}

QRectF Edge::sceneBorder() const
{
	QRectF rect(mSourceNode->coor(), mDestNode->coor());
	return rect.normalized();
}

Edge & Edge::setLength( qreal len )
{
	mLength = len;
	return *this;
}

Edge & Edge::setMotorWayWidth( qreal width )
{
	mMotorWayWidth = width;
	return *this;
}

Edge & Edge::setNonMotorWayWidth( qreal width )
{
	mNonMotorWayWidth = width;
	return *this;
}

Edge & Edge::setWayIsolate( bool isolate )
{
	mWayIsolate = isolate;
	return *this;
}

Edge & Edge::setRoadType( uint type )
{
	mRoadType = type;
	return *this;
}

qreal Edge::length() const
{
	return mLength;
}

qreal Edge::motorWayWidth() const
{
	return mMotorWayWidth;
}

qreal Edge::nonMotorWayWidth() const
{
	return mNonMotorWayWidth;
}

bool Edge::wayIsolate() const
{
	return mWayIsolate;
}

uint Edge::roadType() const
{
	return mRoadType;
}

Edge & Edge::setTrafficType( uint type )
{
	mTrafficType = type;
	return *this;
}

Edge & Edge::setInScale( bool in )
{
	mInScale = in;
	return *this;
}

uint Edge::trafficType() const
{
	return mTrafficType;
}

bool Edge::inScale() const
{
	return mInScale;
}

int Edge::id() const
{
	return mId;
}

Edge & Edge::setId( int id )
{
	mId = id;
	return *this;
}

int Edge::sourceNodeId() const
{
	return mSourceNodeId;
}

int Edge::destNodeId() const
{
	return mDestNodeId;
}

Edge & Edge::setSourceNodeId( int id )
{
	mSourceNodeId = id;
	return *this;
}

Edge & Edge::setDestNodeId( int id )
{
	mDestNodeId = id;
	return *this;
}

int Edge::busNum() const
{
	return mBusNum;
}

Edge & Edge::setBusNum( int num )
{
	mBusNum = num;
	return *this;
}

void Edge::addBus()
{
	mBusNum++;
}

Edge & Edge::setTrafficForbid(RoadPermission* forbid)
{
	mTrafficForbid = forbid;
	return *this;
}

RoadPermission* Edge::trafficForbid() const
{
	return mTrafficForbid;
}

Edge & Edge::setTrafficNumLimit(RoadPermission* p)
{
	mTrafficNumLimit = p;
	return *this;
}

RoadPermission* Edge::trafficNumLimit() const
{
	return mTrafficNumLimit;
}

TrafficVolume* Edge::trafficVolume() const
{
	return mVolume;
}

Edge & Edge::setTrafficVolume(TrafficVolume* volume)
{
	mVolume = volume;
	return *this;
}


