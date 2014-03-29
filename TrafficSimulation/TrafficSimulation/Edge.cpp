#include "Edge.h"



Edge::Edge( GraphicsNodeItem* sourceNode, GraphicsNodeItem* destNode )
{
	mSourceNode = sourceNode;
	mDestNode = destNode;
}

Edge::Edge( const Edge & edge )
{
	mSourceNode = edge.sourceNode();
	mDestNode = edge.destNode();

}


Edge::~Edge(void)
{
}

GraphicsNodeItem* Edge::sourceNode() const
{
	return mSourceNode;
}

GraphicsNodeItem* Edge::destNode() const
{
	return mDestNode;
}

QRectF Edge::border(const QGraphicsItem* edge) const
{
	QPointF p1 = edge->mapFromItem(mSourceNode, QPointF(0,0) );
	QPointF p2 = edge->mapFromItem(mDestNode, QPointF(0,0) );
	QRectF rect(p1, p2);
	return rect.normalized();
}

Edge & Edge::operator=( const Edge & edge )
{
	mSourceNode = edge.sourceNode();
	mDestNode = edge.destNode();
	return *this;
}

bool Edge::operator==( const Edge & edge ) const
{
	return (mDestNode==edge.destNode() ) && (mSourceNode==edge.sourceNode() );
}
