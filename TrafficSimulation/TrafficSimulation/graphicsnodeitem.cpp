#include "graphicsnodeitem.h"
#include <QPainter>

GraphicsNodeItem::GraphicsNodeItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	init();
}

GraphicsNodeItem::GraphicsNodeItem( QPointF p , QGraphicsItem *parent/*=0*/ )
	: QGraphicsItem(parent)
	, mNormPos(p)
{
	init();

}

GraphicsNodeItem::~GraphicsNodeItem()
{

}

void GraphicsNodeItem::setNormPos( QPointF p )
{
	mNormPos = p;
}

QPointF GraphicsNodeItem::normPos() const
{
	return mNormPos;
}

void GraphicsNodeItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawEllipse(QPointF(0,0), mRadius, mRadius);
}

void GraphicsNodeItem::init()
{
	mRadius = 3.0;

	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
}

void GraphicsNodeItem::setNo( int no )
{
	mNo = no;
}

QRectF GraphicsNodeItem::boundingRect() const
{
	return QRectF(-mRadius, -mRadius, 2*mRadius, 2*mRadius);
}

QPainterPath GraphicsNodeItem::shape() const
 {
	 QPainterPath path;
	 path.addEllipse(QPointF(0,0),mRadius,mRadius);
	 return path;
 }

int GraphicsNodeItem::no() const
{
	return mNo;
}
