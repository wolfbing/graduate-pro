#include "EdgeItem.h"

/*
先把这个类作为一个临时的类吧, 因为代码我也不知道该怎样重构
这个类不是用来存放与边先关的数据的, 见Edge类
*/
EdgeItem::EdgeItem( GraphicsNodeItem* sourceNode, GraphicsNodeItem* destNode )
{
	mSourceNode = sourceNode;
	mDestNode = destNode;
}

EdgeItem::EdgeItem( const EdgeItem & edge )
{
	mSourceNode = edge.sourceNode();
	mDestNode = edge.destNode();

}


EdgeItem::~EdgeItem(void)
{
}

GraphicsNodeItem* EdgeItem::sourceNode() const
{
	return mSourceNode;
}

GraphicsNodeItem* EdgeItem::destNode() const
{
	return mDestNode;
}

QRectF EdgeItem::border(const QGraphicsItem* edge) const
{
	QPointF p1 = edge->mapFromItem(mSourceNode, QPointF(0,0) );
	QPointF p2 = edge->mapFromItem(mDestNode, QPointF(0,0) );
	QRectF rect(p1, p2);
	return rect.normalized();
}

EdgeItem & EdgeItem::operator=( const EdgeItem & edge )
{
	mSourceNode = edge.sourceNode();
	mDestNode = edge.destNode();
	return *this;
}

bool EdgeItem::operator==( const EdgeItem & edge ) const
{
	return (mDestNode==edge.destNode() ) && (mSourceNode==edge.sourceNode() );
}
