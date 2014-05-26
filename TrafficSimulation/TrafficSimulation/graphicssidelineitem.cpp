#include "graphicssidelineitem.h"
#include <QPen>
#include <QPainter>
#include "Edge.h"
#include "RoadPermission.h"
#include "TrafficVolume.h"
#include "Capability.h"
#include "Speed.h"

GraphicsSideLineItem::GraphicsSideLineItem(QGraphicsItem *parent)
	: QGraphicsItem(parent)
{
	init();
}

GraphicsSideLineItem::~GraphicsSideLineItem()
{

}



void GraphicsSideLineItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
	QPen pen(mColor,mWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	painter->setPen(pen);
	QLineF line(mEdgeData->sourceNode()->sceneCoor(), mEdgeData->destNode()->sceneCoor() );
	QPointF delta(qCos(line.angle()-90)*mWidth/2.0, qSin(line.angle()-90)*mWidth/2.0);
	QPointF source = mEdgeData->sourceNode()->sceneCoor() + delta;
	QPointF dest = mEdgeData->destNode()->sceneCoor() + delta;
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawLine(source, dest);
}

void GraphicsSideLineItem::init()
{
	mColor = QColor(253,206,102);

	setFlag(ItemSendsGeometryChanges);
	setAcceptHoverEvents(true);
	//setCacheMode(DeviceCoordinateCache);
	setCacheMode(NoCache);
}

QRectF GraphicsSideLineItem::boundingRect() const
{
	QPointF source = mEdgeData->sourceNode()->sceneCoor();
	QPointF dest = mEdgeData->destNode()->sceneCoor();
	QLineF line(source, dest);
	qreal ang = line.angle();
	QPointF delta(qCos(line.angle()-90)*mWidth, qSin(line.angle()-90)*mWidth);
	QPointF tmpPoint1 = source + delta;
	QPointF tmpPoint2 = dest + delta;
	qreal left = qMin(qMin(qMin( source.x(), dest.x())
		, tmpPoint1.x() ), tmpPoint2.x() );
	qreal right = qMax(qMax(qMax(source.x(), dest.x())
		,  tmpPoint1.x() ), tmpPoint2.x() );
	qreal top = qMin(qMin(qMin(source.y(), dest.y())
		, tmpPoint1.y() ), tmpPoint2.y() );
	qreal bottom = qMax(qMax(qMax(source.y(), dest.y())
		,  tmpPoint1.y() ), tmpPoint2.y() );
	return QRectF(left, top, qAbs(right-left), qAbs(top-bottom));
		
}

QPainterPath GraphicsSideLineItem::shape() const
{
	QPointF source = mEdgeData->sourceNode()->sceneCoor();
	QPointF dest = mEdgeData->destNode()->sceneCoor();
	QLineF line(source, dest);
	QPointF delta(qCos(line.angle()-90)*mWidth, qSin(line.angle()-90)*mWidth);
	QPointF tmpPoint1 = source + delta;
	QPointF tmpPoint2 = dest + delta;
	QPainterPath path;
	path.moveTo(tmpPoint1);
	path.lineTo(tmpPoint2);
	path.lineTo(dest);
	path.lineTo(source);
	path.lineTo(tmpPoint1);
	return path;
}

GraphicsSideLineItem & GraphicsSideLineItem::setEdgeData(Edge* edge)
{
	mEdgeData = edge;
	return *this;
}

void GraphicsSideLineItem::advance()
{
	prepareGeometryChange();
}

GraphicsSideLineItem & GraphicsSideLineItem::setWidth(qreal width)
{
	mWidth = width;
	return *this;
}

GraphicsSideLineItem & GraphicsSideLineItem::setColor(QColor color)
{
	mColor = color;
	return *this;
}

void GraphicsSideLineItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	QString msg = QStringLiteral("路段编号: ") + QString::number(mEdgeData->sourceNode()->no())
		+ "-" + QString::number(mEdgeData->destNode()->no()) + ";  ";
	switch (mGraphType)
	{
	case BusNumGraph:
		msg += QStringLiteral("公交线路数量: ") + QString::number(mEdgeData->busNum());
		break;
	case RoadLevelGraph:
		msg += QStringLiteral("道路等级: ") + QString::number(mEdgeData->roadLevel());
		break;
	case GraphicsSideLineItem::RoadTypeGraph:
		msg += QStringLiteral("道路类型: ") + QString::number(mEdgeData->roadType());
		break;
	case TrafficTypeGraph:
		msg += QStringLiteral("管理类型: ") + QString::number(mEdgeData->trafficType());
		break;
	case BikeForbidGraph:
		msg += QStringLiteral("自行车禁行: ") + (mEdgeData->trafficForbid()->permitBike() ? QStringLiteral("是") : QStringLiteral("否")) ;
		break;
	case CarForbidGraph:
		msg += QStringLiteral("客车禁行: ") + ( mEdgeData->trafficForbid()->permitCar() ? QStringLiteral("是") : QStringLiteral("否"));
		break;
	case MotorForbidGraph:
		msg += QStringLiteral("摩托车禁行: ") + ( mEdgeData->trafficForbid()->permitMotor() ? QStringLiteral("是") :QStringLiteral("否"));
		break;
	case TaxiForbidGraph:
		msg += QStringLiteral("出租车禁行: ") + ( mEdgeData->trafficForbid()->permitTaxi() ? QStringLiteral("是") : QStringLiteral("否"));
		break;
	case BusForbidGraph:
		msg += QStringLiteral("公交车禁行: ") + ( mEdgeData->trafficForbid()->permitBus() ? QStringLiteral("是") : QStringLiteral("否"));
		break;
	case TruckForbidGraph:
		msg += QStringLiteral("货车禁行: ") + ( mEdgeData->trafficForbid()->permitTruck() ? QStringLiteral("是") : QStringLiteral("否"));
		break;
	case CarLimitGraph:
		msg += QStringLiteral("客车限号通行类: ") + QString::number(mEdgeData->trafficNumLimit()->permitCar());
		break;
	case MotorLimitGraph:
		msg += QStringLiteral("摩托车限号通行类: ") + QString::number(mEdgeData->trafficNumLimit()->permitMotor());
		break;
	case  TaxiLimitGraph:
		msg += QStringLiteral("出租车限号通行类: ") + QString::number(mEdgeData->trafficNumLimit()->permitTaxi());
		break;
	case TruckLimitGraph:
		msg += QStringLiteral("货车限号通行类: ") + QString::number(mEdgeData->trafficNumLimit()->permitTruck());
		break;
	case MotorVolumeGraph:
		msg += QStringLiteral("机动车交通量: ") + QString::number(mEdgeData->trafficVolume()->motorVolume());
		break;
	case NonMotorVolumeGraph:
		msg += QStringLiteral("非机动车交通量: ") + QString::number(mEdgeData->trafficVolume()->nonMotorVolume());
		break;
	case CarVolumeGraph:
		msg += QStringLiteral("客车交通量: ") + QString::number(mEdgeData->trafficVolume()->carVolume());
		break;
	case BusVolumeGraph:
		msg += QStringLiteral("公交车交通量: ") + QString::number(mEdgeData->trafficVolume()->busVolume());
		break;
	case TaxiVolumeGraph:
		msg += QStringLiteral("出租车交通量: ") + QString::number(mEdgeData->trafficVolume()->taxiVolume());
		break;
	case MotorbikeVolumeGraph:
		msg += QStringLiteral("摩托车交通量: ") + QString::number(mEdgeData->trafficVolume()->motorbikeVolume());
		break;
	case TruckVolumeGraph:
		msg += QStringLiteral("货车交通量: ") + QString::number(mEdgeData->trafficVolume()->truckVolume());
		break;
	case MotorCapabilityGraph:
		msg += QStringLiteral("负荷量: ") + QString::number(mEdgeData->trafficCapability()->motorCapability());
		break;
	case NonMotorCapabilityGraph:
		msg += QStringLiteral("负荷量: ") + QString::number(mEdgeData->trafficCapability()->nonMotorCapability());
		break;
	case SpeedGraph:
		msg += QStringLiteral("平均速度: ") + QString::number(mEdgeData->speed()->speed());
		break;
	default:
		break;
	}
		
	emit sendTmpInfoToStatus(msg);
}

void GraphicsSideLineItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	emit clearTmpInfoFromStatus();
}

GraphicsSideLineItem & GraphicsSideLineItem::setGraphType(GraphType type)
{
	mGraphType = type;
	return *this;
}

Edge* GraphicsSideLineItem::edgeData() const
{
	return mEdgeData;
}

void GraphicsSideLineItem::updateAttr(QColor color, qreal width)
{
	mColor = color;
	mWidth = width;
	update();
}
