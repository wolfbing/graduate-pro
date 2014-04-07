#include "node.h"
#include <QtMath>

// 包含位置和编号信息的节点
Node::Node( QPointF p, int no)
{
	mCoor = p;
	mNo = no;
}

Node::Node( const Node & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
}

bool Node::operator==( const Node & node ) const
{
	return (this->mCoor==node.mCoor) && (this->mNo==node.mNo);
}

Node & Node::operator=( const Node & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
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


qreal length( QPair<Node,Node> pair )
{
	QPointF p1 = pair.first.coor();
	QPointF p2 = pair.second.coor();
	QPointF delta = p1 - p2;
	return qSqrt(qPow(delta.x(),2)+qPow(delta.y(),2));

}



