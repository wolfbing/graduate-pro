#include "trafficnumlimitgraphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "RoadPermission.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

TrafficNumLimitGraphicsScene::TrafficNumLimitGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
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

void TrafficNumLimitGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	GraphicsSideLineItem * item;
	QListIterator<GraphicsSideLineItem*> ite(mSideLineItemList);
	while (ite.hasNext())
	{
		item = ite.next();
		item->advance();
	}
}

void TrafficNumLimitGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QStringLiteral("不限号"), LegendElement::LINE, mWidthList.at(0), mColorList.at(0) );
	elements << LegendElement(QStringLiteral("单双号通行"), LegendElement::LINE, mWidthList.at(1), mColorList.at(1) );
	elements << LegendElement(QStringLiteral("末号通行"), LegendElement::LINE, mWidthList.at(2), mColorList.at(2) );
	Legend* legend = new Legend(elements);
	LegendProxy* proxy = new LegendProxy(legend);
	addItem(proxy);
}

