#include "trafficnumlimitgraphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "RoadPermission.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

TrafficNumLimitGraphicsScene::TrafficNumLimitGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficNumLimitGraphicsScene::~TrafficNumLimitGraphicsScene()
{

}

void TrafficNumLimitGraphicsScene::init()
{
	mColorList << QColor(223,35,40) << QColor(0,122,204) << QColor(240,129,0);
	mWidthList << 3 << 3 << 3;
	mZValueList << 3 << 2 << 1;
	mLabelTextList << QStringLiteral("不限号") << QStringLiteral("单双号通行")
		<< QStringLiteral("末号通行");
}

void TrafficNumLimitGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	GraphicsSideLineItem* item;
	Edge* tmpEdgeData;
	int index;
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		item = new GraphicsSideLineItem;
		item->setEdgeData(tmpEdgeData);
		switch (mLimitType)
		{
		case TrafficNumLimitGraphicsScene::CarLimit:
			index = tmpEdgeData->trafficNumLimit()->permitCar();
			item->setGraphType(GraphicsSideLineItem::CarLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::MotorLimit:
			index = tmpEdgeData->trafficNumLimit()->permitMotor();
			item->setGraphType(GraphicsSideLineItem::MotorLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::TruckLimit:
			index = tmpEdgeData->trafficNumLimit()->permitTruck();
			item->setGraphType(GraphicsSideLineItem::TaxiLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::TaxiLimit:
			index = tmpEdgeData->trafficNumLimit()->permitTaxi();
			item->setGraphType(GraphicsSideLineItem::TruckLimitGraph);
			break;
		default:
			break;
		}
		item->setColor(mColorList.at(index)).setWidth(mWidthList.at(index)).setZValue(mZValueList.at(index));
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);

	}

}

TrafficNumLimitGraphicsScene& TrafficNumLimitGraphicsScene::setLimitType(LimitType limit)
{
	mLimitType = limit;
	return *this;
}

void TrafficNumLimitGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::LINE, mWidthList.at(0), mColorList.at(0) );
	elements << LegendElement(mLabelTextList.at(1), LegendElement::LINE, mWidthList.at(1), mColorList.at(1) );
	elements << LegendElement(mLabelTextList.at(2), LegendElement::LINE, mWidthList.at(2), mColorList.at(2) );
	Legend* legend = new Legend(elements);
	mLegendProxy = new LegendProxy(legend);
	addItem(mLegendProxy);
}

void TrafficNumLimitGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	GraphicsSideLineItem* item;
	Edge* tmpEdgeData;
	int index;
	while (itemIte.hasNext())
	{
		item = itemIte.next();
		tmpEdgeData = item->edgeData();
		switch (mLimitType)
		{
		case TrafficNumLimitGraphicsScene::CarLimit:
			index = tmpEdgeData->trafficNumLimit()->permitCar();
			item->setGraphType(GraphicsSideLineItem::CarLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::MotorLimit:
			index = tmpEdgeData->trafficNumLimit()->permitMotor();
			item->setGraphType(GraphicsSideLineItem::MotorLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::TruckLimit:
			index = tmpEdgeData->trafficNumLimit()->permitTruck();
			item->setGraphType(GraphicsSideLineItem::TaxiLimitGraph);
			break;
		case TrafficNumLimitGraphicsScene::TaxiLimit:
			index = tmpEdgeData->trafficNumLimit()->permitTaxi();
			item->setGraphType(GraphicsSideLineItem::TruckLimitGraph);
			break;
		default:
			break;
		}
		item->updateAttr(mColorList.at(index), mWidthList.at(index));
	}
	mLegendProxy->updateAttr(mColorList, mWidthList);

}

