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


