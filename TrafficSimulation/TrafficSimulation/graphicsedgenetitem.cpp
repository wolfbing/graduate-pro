#include "graphicsedgenetitem.h"
#include <QPainter>
#include <QPainterPath>

GraphicsEdgeNetItem::GraphicsEdgeNetItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	setFlag(ItemSendsGeometryChanges);
	init();
}

GraphicsEdgeNetItem::~GraphicsEdgeNetItem()
{

}


QRectF GraphicsEdgeNetItem::boundingRect() const
{
	QListIterator<Edge*> ite(mEdgeDataList);
	qreal left, right, top, bottom;
	if(!ite.hasNext())
		return QRectF(0,0,0,0);
	Edge* edgeData = ite.next();
	QRectF rect = edgeData->sceneBorder();
	left = rect.left();
	right = rect.right();
	top = rect.top();
	bottom = rect.bottom();
	while (ite.hasNext())
	{
		edgeData = ite.next();
		rect = edgeData->sceneBorder();
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

void GraphicsEdgeNetItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
	QPainterPath path;
	QListIterator<Edge*> ite(mEdgeDataList);
	Edge * edgeData;
	while (ite.hasNext())
	{
		edgeData = ite.next();
		QPointF sourcePos = edgeData->sourceNode()->sceneCoor();
		QPointF destPos = edgeData->destNode()->sceneCoor();
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

QPainterPath GraphicsEdgeNetItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}

void GraphicsEdgeNetItem::advance()
{
	prepareGeometryChange();
	
}

GraphicsEdgeNetItem & GraphicsEdgeNetItem::setWidth( qreal width )
{
	mEdgeWidth = width;
	return *this;
}

GraphicsEdgeNetItem & GraphicsEdgeNetItem::setBorderColor( QColor borderColor )
{
	mBorderColor = borderColor;
	return *this;
}

GraphicsEdgeNetItem & GraphicsEdgeNetItem::setInnerColor( QColor innerColor )
{
	mInnerColor = innerColor;
	return *this;
}

GraphicsEdgeNetItem & GraphicsEdgeNetItem::setHaveBorder( bool haveBorder )
{
	mHaveBorder = haveBorder;
	return *this;
}

void GraphicsEdgeNetItem::init()
{
	mHaveBorder = true;
	mBorderColor = QColor(203,168,87);
	mInnerColor = QColor(253,206,102);
	mEdgeWidth = 4.0;
}

qreal GraphicsEdgeNetItem::edgeWidth() const
{
	return mEdgeWidth;
}

QColor GraphicsEdgeNetItem::innerColor() const
{
	return mInnerColor;
}

QColor GraphicsEdgeNetItem::borderColor() const
{
	return mBorderColor;
}

void GraphicsEdgeNetItem::addEdgeData( Edge* edgeData )
{
	mEdgeDataList << edgeData;
}
