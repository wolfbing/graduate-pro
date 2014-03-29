#include "graphicsnodeitem.h"
#include <QPainter>
#include "graphicsnodenotextitem.h"
#include <QStringListIterator>

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

GraphicsNodeItem::GraphicsNodeItem( QPointF normPos, int no, QGraphicsItem *parent/*=0*/ )
	: QGraphicsItem(parent)
	, mNormPos(normPos)
	, mNo(no)
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
	checkNoItemVisible();
	painter->setRenderHint(QPainter::Antialiasing);
	if(mHaveBorder)
		painter->setPen(mBorderColor);
	else
	{
		painter->setPen(Qt::NoPen);
	}
	painter->setBrush(QBrush(mInnerColor) );
	painter->drawEllipse(-mRadius, -mRadius, 2*mRadius, 2*mRadius);
}

void GraphicsNodeItem::init()
{
	// 基本参数 
	mRadius = 4.0;
	mHaveBorder = true;
	mBorderColor = QColor(38,0,0);
	mInnerColor = QColor(178,73,77);
	// 事件设置
	setAcceptHoverEvents(true);
	// 绘制设置
	setFlag(ItemSendsScenePositionChanges);
	setFlag(ItemSendsGeometryChanges);
	setCacheMode(DeviceCoordinateCache);
	setZValue(1.0);
	// 邻居
	mNeignbour = 0;
	mNoTextItem = 0;
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
	 path.addEllipse(-mRadius, -mRadius,2*mRadius,2*mRadius);
	 return path;
 }

int GraphicsNodeItem::no() const
{
	return mNo;
}

GraphicsNodeItem & GraphicsNodeItem::setRadius( qreal radius )
{
	mRadius = radius;
	return *this;
}

GraphicsNodeItem & GraphicsNodeItem::setHaveBorder( bool haveBorder )
{
	mHaveBorder = haveBorder;
	return *this;
}

GraphicsNodeItem & GraphicsNodeItem::setBorderColor( QColor borderColor )
{
	mBorderColor = borderColor;
	return *this;
}

GraphicsNodeItem & GraphicsNodeItem::setInnerColor( QColor innerColor )
{
	mInnerColor = innerColor;
	return *this;
}

void GraphicsNodeItem::checkNeighbour( GraphicsNodeItem* item )
{
	if (!mNeignbour)
	{
		mNeignbour = item;
		mNearestDistance = QLineF(mNormPos, item->mNormPos).length();
	}
	else
	{
		qreal len = QLineF(mNormPos, item->mNormPos).length();
		if (len<mNearestDistance)
		{
			mNeignbour = item;
			mNearestDistance = len;
		}
	}
}

qreal GraphicsNodeItem::radius() const
{
	return mRadius;
}

void GraphicsNodeItem::checkNoItemVisible()
{
	
	if(!mNoTextItem)
		return ;
	if(!mNeignbour)
		return ;
	qreal dis = QLineF(mapToItem(mNeignbour,0,0), QPointF(0,0) ).length();
	GraphicsNodeNoTextItem* textItem = qgraphicsitem_cast<GraphicsNodeNoTextItem*>(mNoTextItem);
	if (dis>30)
	{
		textItem->show();
	}
	else
	{
		textItem->hide();
	}
}

QVariant GraphicsNodeItem::itemChange( GraphicsItemChange change, const QVariant &value )
{
	//switch (change)
	//{
	//case QGraphicsItem::ItemPositionChange:
	//	checkNoItemVisible();
	//	break;
	//default:
	//	break;
	//}
	return QGraphicsItem::itemChange(change, value);
}

GraphicsNodeItem & GraphicsNodeItem::setNoTextItem( QGraphicsItem* item )
{
	mNoTextItem = item;
	return *this;
}

void GraphicsNodeItem::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
	QString str = QString::number(mNo);
	emit sendNodeInfoToStatus(QStringLiteral("节点编号：")+str);
}


void GraphicsNodeItem::hoverLeaveEvent( QGraphicsSceneHoverEvent *event )
{
	emit clearNodeInfoFromStatus();
}


