#include "graphicsnodeitem.h"
#include <QPainter>
#include "graphicsnodenotextitem.h"
#include <QStringListIterator>

GraphicsNodeItem::GraphicsNodeItem(QGraphicsItem *parent)
	: QGraphicsItem(parent), Communicate()
{
	init();
}



GraphicsNodeItem::~GraphicsNodeItem()
{

}


void GraphicsNodeItem::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
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
	mType = No;
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
		mNearestDistance = QLineF(mNodeData->coor(), item->mNodeData->coor()).length();
	}
	else
	{
		qreal len = QLineF(mNodeData->coor(), item->mNodeData->coor()).length();
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


void GraphicsNodeItem::hoverEnterEvent( QGraphicsSceneHoverEvent *event )
{
	QString str = QString::number(mNodeData->no());
	if(mType==Junction)
		str += QStringLiteral(";  交叉口类型: ")+QString::number(mNodeData->junctionType());
	if (mType==Restriction)
		str += QStringLiteral(";  转向限制: ") + QString::number(mNodeData->haveTurnRestrict() ? 1:0);
	emit sendTmpInfoToStatus(QStringLiteral("节点编号：")+str);
}


void GraphicsNodeItem::hoverLeaveEvent( QGraphicsSceneHoverEvent *event )
{
	emit clearTmpInfoFromStatus();
}

QColor GraphicsNodeItem::borderColor() const
{
	return mBorderColor;
}

QColor GraphicsNodeItem::innerColor() const
{
	return mInnerColor;
}

GraphicsNodeItem & GraphicsNodeItem::setNodeData( Node * node )
{
	mNodeData = node;
	return *this;
}

Node * GraphicsNodeItem::nodeData() const
{
	return mNodeData;
}

GraphicsNodeItem & GraphicsNodeItem::setNodeItemType( NodeItemType type )
{
	mType = type;
	return *this;
}


