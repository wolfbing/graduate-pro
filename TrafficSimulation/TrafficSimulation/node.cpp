#include "node.h"
#include <QtMath>

// 包含位置和编号信息的节点
NodeWithCoorNo::NodeWithCoorNo( QPointF p, int no)
{
	mCoor = p;
	mNo = no;
}

NodeWithCoorNo::NodeWithCoorNo( const NodeWithCoorNo & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
}

bool NodeWithCoorNo::operator==( const NodeWithCoorNo & node ) const
{
	return (this->mCoor==node.mCoor) && (this->mNo==node.mNo);
}

NodeWithCoorNo & NodeWithCoorNo::operator=( const NodeWithCoorNo & node )
{
	mCoor = node.mCoor;
	mNo = node.mNo;
	return *this;
}


Rect NodeWithCoorNo::border() const
{
	return Rect(mCoor.x(), mCoor.y(), 0, 0);
}

void NodeWithCoorNo::norm( qreal factor, QPointF c )
{
	mCoor = (mCoor-c)/factor;
}


qreal length( QPair<NodeWithCoorNo,NodeWithCoorNo> pair )
{
	QPointF p1 = pair.first.mCoor;
	QPointF p2 = pair.second.mCoor;
	QPointF delta = p1 - p2;
	return qSqrt(qPow(delta.x(),2)+qPow(delta.y(),2));

}
