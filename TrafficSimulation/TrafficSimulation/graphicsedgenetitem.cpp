#include "graphicsedgenetitem.h"
#include <QPainter>
#include <QPainterPath>

GraphicsEdgetNetItem::GraphicsEdgetNetItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	setFlag(ItemSendsGeometryChanges);
	init();
}

GraphicsEdgetNetItem::~GraphicsEdgetNetItem()
{

}

void GraphicsEdgetNetItem::addEdge(const Edge & edge )
{
	mEdges << edge;
	edge.sourceNode()->checkNeighbour(edge.destNode() );
	edge.destNode()->checkNeighbour(edge.sourceNode() );
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
	if (mHaveBorder)
	{
		QPen outerPen(mBorderColor);
		outerPen.setWidthF(mEdgeWidth);
		painter->setPen(outerPen);
		painter->drawPath(path);
	}
	QPen innerPen(mInnerColor);
	innerPen.setWidthF(mEdgeWidth-(mHaveBorder ? 2.0 : 0.0) );
	painter->setPen(innerPen);
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

GraphicsEdgetNetItem & GraphicsEdgetNetItem::setWidth( qreal width )
{
	mEdgeWidth = width;
	return *this;
}

GraphicsEdgetNetItem & GraphicsEdgetNetItem::setBorderColor( QColor borderColor )
{
	mBorderColor = borderColor;
	return *this;
}

GraphicsEdgetNetItem & GraphicsEdgetNetItem::setInnerColor( QColor innerColor )
{
	mInnerColor = innerColor;
	return *this;
}

GraphicsEdgetNetItem & GraphicsEdgetNetItem::setHaveBorder( bool haveBorder )
{
	mHaveBorder = haveBorder;
	return *this;
}

void GraphicsEdgetNetItem::init()
{
	mHaveBorder = true;
	mBorderColor = QColor(203,168,87);
	mInnerColor = QColor(253,206,102);
	mEdgeWidth = 4.0;
}
