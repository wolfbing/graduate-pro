#include "trafficforbidgraphicsscene.h"
#include "Edge.h"
#include "graphicssidelineitem.h"
#include "RoadPermission.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


TrafficForbidGraphicsScene::TrafficForbidGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficForbidGraphicsScene::~TrafficForbidGraphicsScene()
{

}

void TrafficForbidGraphicsScene::init()
{
	mColorList << QColor(223,35,40) << QColor(50,158,28);
	mWidthList << 3 << 3;
	mZValueList << 2 << 1;
}

void TrafficForbidGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge* tmpEdgeData;
	GraphicsSideLineItem* item;
	int index;
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		item = new GraphicsSideLineItem;
		bool forbid;
		switch (mForbidType)
		{
		case BikeForbid:
			forbid = tmpEdgeData->trafficForbid()->permitBike();
			item->setGraphType(GraphicsSideLineItem::BikeForbidGraph);
			break;
		case CarForbid:
			forbid = tmpEdgeData->trafficForbid()->permitCar();
			item->setGraphType(GraphicsSideLineItem::CarForbidGraph);
			break;
		case MotorForbid:
			forbid = tmpEdgeData->trafficForbid()->permitMotor();
			item->setGraphType(GraphicsSideLineItem::MotorForbidGraph);
			break;
		case TaxiForbid:
			forbid = tmpEdgeData->trafficForbid()->permitTaxi();
			item->setGraphType(GraphicsSideLineItem::TaxiForbidGraph);
			break;
		case BusForbid:
			forbid = tmpEdgeData->trafficForbid()->permitBus();
			item->setGraphType(GraphicsSideLineItem::BusForbidGraph);
			break;
		case TruckForbid:
			forbid = tmpEdgeData->trafficForbid()->permitTruck();
			item->setGraphType(GraphicsSideLineItem::TruckForbidGraph);
			break;
		default:
			break;
		}
		index =forbid ? 0 : 1;
		item->setEdgeData(tmpEdgeData).setColor(mColorList.at(index)).setWidth(mWidthList.at(index))
			.setZValue(mZValueList.at(index));
		mSideLineItemList << item;
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		addItem(item);

	}
}

TrafficForbidGraphicsScene& TrafficForbidGraphicsScene::setForbidType(ForbidType t)
{
	mForbidType = t;
	return *this;
}

void TrafficForbidGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("禁止通行"),LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement(QStringLiteral("允许通行"),LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy(legend);
	addItem(proxy);

}

void TrafficForbidGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	GraphicsSideLineItem* item;
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		item->advance();
	}
}

void TrafficForbidGraphicsScene::doSomething()
{

}
