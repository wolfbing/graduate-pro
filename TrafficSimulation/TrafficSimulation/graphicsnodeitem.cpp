#include "graphicsnodeitem.h"
#include <QPainter>
#include "graphicsnodenotextitem.h"
#include <QStringListIterator>
#include "TrafficVolume.h"
#include "Capability.h"

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
	switch (mType)
	{
	case GraphicsNodeItem::No:
		break;
	case GraphicsNodeItem::Junction:
		str += QStringLiteral(";  交叉口类型: ")+QString::number(mNodeData->junctionType());
		break;
	case GraphicsNodeItem::Restriction:
		str += QStringLiteral(";  转向限制: ") + QString::number(mNodeData->haveTurnRestrict() ? 1:0);
		break;
	case GraphicsNodeItem::MotorVolumeGraph:
		str += QStringLiteral("机动车交通量") + QString::number(mNodeData->trafficVolume()->motorVolume());
		break;
	case GraphicsNodeItem::NonMotorVolumeGraph:
		str += QStringLiteral("非机动车交通量") + QString::number(mNodeData->trafficVolume()->nonMotorVolume());
		break;
	case GraphicsNodeItem::CarVolumeGraph:
		str += QStringLiteral("客车交通量") + QString::number(mNodeData->trafficVolume()->carVolume());
		break;
	case GraphicsNodeItem::BusVolumeGraph:
		str += QStringLiteral("公交车交通量") + QString::number(mNodeData->trafficVolume()->busVolume());
		break;
	case GraphicsNodeItem::MotorbikeVolumeGraph:
		str += QStringLiteral("摩托车交通量") + QString::number(mNodeData->trafficVolume()->motorbikeVolume());
		break;
	case GraphicsNodeItem::TaxiVolumeGraph:
		str += QStringLiteral("出租车交通量") + QString::number(mNodeData->trafficVolume()->taxiVolume());
		break;
	case GraphicsNodeItem::TruckVolumeGraph:
		str += QStringLiteral("货车交通量") + QString::number(mNodeData->trafficVolume()->truckVolume());
		break;
	case MotorCapabilityGraph:
		str += QStringLiteral("") + QString::number(mNodeData->trafficCapability()->motorCapability());
		break;
	case NonMotorCapabilityGraph:
		str += QStringLiteral("") + QString::number(mNodeData->trafficCapability()->nonMotorCapability());
		break;
	default:
		break;
	}
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

GraphicsNodeItem & GraphicsNodeItem::setGraphType(NodeItemType type)
{
	mType = type;
	return *this;
}

void GraphicsNodeItem::updateAttr(QColor innerColor, QColor borderColor, qreal radius, bool haveBorder)
{
	mInnerColor = innerColor;
	mBorderColor = borderColor;
	mRadius = radius;
	mHaveBorder = haveBorder;
	update();
}


