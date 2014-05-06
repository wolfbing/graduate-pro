#include "trafficroadvolumegraphicsscene.h"
#include "graphicssidelineitem.h"
#include "Edge.h"
#include "TrafficVolume.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

TrafficRoadVolumeGraphicsScene::TrafficRoadVolumeGraphicsScene(QObject *parent)
	: RoadGraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficRoadVolumeGraphicsScene::~TrafficRoadVolumeGraphicsScene()
{

}

void TrafficRoadVolumeGraphicsScene::init()
{
	mColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40);
	mWidthList << 3 << 3 << 3 << 3 << 3 << 3;
	mZValueList << 1 << 2 << 3 << 4 << 5 << 6;
	mLabelTextList << "<=100" << "100-200" << "200-500" << "500-1000" << "1000-2000" << ">=2000";

}

void TrafficRoadVolumeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement("<=100", LegendElement::LINE, mWidthList.at(0), mColorList.at(0));
	elements << LegendElement("100-200", LegendElement::LINE, mWidthList.at(1), mColorList.at(1));
	elements << LegendElement("200-500", LegendElement::LINE, mWidthList.at(2), mColorList.at(2));
	elements << LegendElement("500-1000", LegendElement::LINE, mWidthList.at(3), mColorList.at(3));
	elements << LegendElement("1000-2000", LegendElement::LINE, mWidthList.at(4), mColorList.at(4));
	elements << LegendElement(">=2000", LegendElement::LINE, mWidthList.at(5), mColorList.at(5));
	Legend* legend = new Legend(elements);
	mLegendProxy = new LegendProxy(legend);
	addItem(mLegendProxy);
}

void TrafficRoadVolumeGraphicsScene::addItems()
{
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge* tmpEdgeData;
	qreal volume;
	GraphicsSideLineItem * item;
	int index;
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		item = new GraphicsSideLineItem;
		switch (mVolumeType)
		{
		case TrafficRoadVolumeGraphicsScene::MotorVolume:
			volume = tmpEdgeData->trafficVolume()->motorVolume();
			item->setGraphType(GraphicsSideLineItem::MotorVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::NonMotorVolume:
			volume = tmpEdgeData->trafficVolume()->nonMotorVolume();
			item->setGraphType(GraphicsSideLineItem::NonMotorVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::CarVolume:
			volume = tmpEdgeData->trafficVolume()->carVolume();
			item->setGraphType(GraphicsSideLineItem::CarVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::BusVolume:
			volume = tmpEdgeData->trafficVolume()->busVolume();
			item->setGraphType(GraphicsSideLineItem::BusVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::MotorbikeVolume:
			volume = tmpEdgeData->trafficVolume()->motorbikeVolume();
			item->setGraphType(GraphicsSideLineItem::MotorbikeVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::TaxiVolume:
			volume = tmpEdgeData->trafficVolume()->taxiVolume();
			item->setGraphType(GraphicsSideLineItem::TaxiVolumeGraph);
			break;
		case TrafficRoadVolumeGraphicsScene::TruckVolume:
			volume = tmpEdgeData->trafficVolume()->truckVolume();
			item->setGraphType(GraphicsSideLineItem::TruckVolumeGraph);
			break;
		default:
			break;
		}
		if(volume<=100)
			index = 0;
		else if(volume<=200)
			index = 1;
		else if(volume<=500)
			index = 2;
		else if(volume<=1000)
			index = 3;
		else if(volume<=2000)
			index = 4;
		else
			index = 5;

		item->setEdgeData(tmpEdgeData).setColor(mColorList.at(index)).setWidth(mWidthList.at(index))
			.setZValue(mZValueList.at(index));
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		mSideLineItemList << item;
		addItem(item);

	}


}

TrafficRoadVolumeGraphicsScene& TrafficRoadVolumeGraphicsScene::setVolumeType(VolumeType type)
{
	mVolumeType = type;
	return *this;
}

void TrafficRoadVolumeGraphicsScene::updateItemsAttr()
{
	GraphicsSideLineItem* item;
	QListIterator<GraphicsSideLineItem*> itemIte(mSideLineItemList);
	qreal volume;
	int index;
	Edge* tmpEdgeData;
	while (itemIte.hasNext()){
		item = itemIte.next();
		tmpEdgeData = item->edgeData();
		switch (mVolumeType)
		{
		case TrafficRoadVolumeGraphicsScene::MotorVolume:
			volume = tmpEdgeData->trafficVolume()->motorVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::NonMotorVolume:
			volume = tmpEdgeData->trafficVolume()->nonMotorVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::CarVolume:
			volume = tmpEdgeData->trafficVolume()->carVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::BusVolume:
			volume = tmpEdgeData->trafficVolume()->busVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::MotorbikeVolume:
			volume = tmpEdgeData->trafficVolume()->motorbikeVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::TaxiVolume:
			volume = tmpEdgeData->trafficVolume()->taxiVolume();
			break;
		case TrafficRoadVolumeGraphicsScene::TruckVolume:
			volume = tmpEdgeData->trafficVolume()->truckVolume();
			break;
		default:
			break;
		}
		if(volume<=100)
			index = 0;
		else if(volume<=200)
			index = 1;
		else if(volume<=500)
			index = 2;
		else if(volume<=1000)
			index = 3;
		else if(volume<=2000)
			index = 4;
		else
			index = 5;
		item->updateAttr(mColorList.at(index), mWidthList.at(index));
	}
	mLegendProxy->updateAttr(mColorList, mWidthList);
}


