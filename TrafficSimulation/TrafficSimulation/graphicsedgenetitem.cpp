#include "graphicsedgenetitem.h"
#include <QPainter>
#include <QPainterPath>

GraphicsEdgetNetItem::GraphicsEdgetNetItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	setFlag(ItemSendsGeometryChanges);
}

GraphicsEdgetNetItem::~GraphicsEdgetNetItem()
{

}

void GraphicsEdgetNetItem::addEdge(const Edge & edge )
{
	mEdges << edge;
}

QRectF GraphicsEdgetNetItem::boundingRect() const
{
	QListIterator<Edge> ite(mEdges);
	qreal left, right, top, bottom;
	if(!ite.hasNext())
		return QRectF(0,0,0,0);
	Edge edge = ite.next();
	QRectF rect = edge.border(this);
	left = rect.left();
	right = rect.right();
	top = rect.top();
	bottom = rect.bottom();
	while (ite.hasNext())
	{
		edge = ite.next();
		rect = edge.border(this);
		if(rect.left()<left)
			left = rect.left();
		if(rect.right()>right)
			right = rect.right();
		if(rect.top()<top)
			top = rect.top();
		if(rect.bottom()>bottom)
			bottom = rect.bottom();
	}
	return QRectF(left, top, qAbs(right-left), qAbs(bottom-top));

}

void GraphicsEdgetNetItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
	QPainterPath path;
	QListIterator<Edge> ite(mEdges);
	Edge edge;
	GraphicsNodeItem *source, *dest;
	while (ite.hasNext())
	{
		edge = ite.next();
		source = edge.sourceNode();
		dest = edge.destNode();
		QPointF sourcePos = mapFromItem(source, QPointF(0,0) );
		QPointF destPos = mapFromItem(dest, QPointF(0,0) );
		path.moveTo(sourcePos);
		path.lineTo(destPos);
	}
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawPath(path);
}

QPainterPath GraphicsEdgetNetItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void GraphicsEdgetNetItem::advance()
{
	prepareGeometryChange();
	
}
