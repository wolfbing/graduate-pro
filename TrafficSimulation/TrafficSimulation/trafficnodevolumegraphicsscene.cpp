#include "trafficnodevolumegraphicsscene.h"
#include "Edge.h"
#include "node.h"
#include "graphicsedgenetitem.h"
#include "graphicsnodeitem.h"
#include "TrafficVolume.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"


TrafficNodeVolumeGraphicsScene::TrafficNodeVolumeGraphicsScene(QObject *parent)
	: CommonNodeGraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficNodeVolumeGraphicsScene::~TrafficNodeVolumeGraphicsScene()
{

}

TrafficNodeVolumeGraphicsScene& TrafficNodeVolumeGraphicsScene::setVolumeType(VolumeType type)
{
	mVolumeType = type;
	return *this;
}

void TrafficNodeVolumeGraphicsScene::init()
{
	mBorderColorList << QColor() << QColor() << QColor() << QColor() << QColor() << QColor() << QColor(203,168,87);
	mInnerColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40) <<  QColor(253,206,102);
	mSizeList << 4 << 4 << 4 << 4 << 4 << 4 << 4;
	mHaveBorderList << true << true << true << true << true << true << true;
	mLabelTextList << "<=100" << "100-200" << "200-500" << "500-1000" << "1000-2000" << ">=2000" << QStringLiteral("Â·¶Î");

}

void TrafficNodeVolumeGraphicsScene::addItems()
{
	QListIterator<Node*> nodeIte(mNodeDataList);
	GraphicsNodeItem * item;
	qreal volume;
	Node* tmpNodeData;
	int index;
	while (nodeIte.hasNext())
	{
		tmpNodeData = nodeIte.next();
		item = new GraphicsNodeItem;

		switch (mVolumeType)
		{
		case TrafficNodeVolumeGraphicsScene::MotorVolume:
			volume = tmpNodeData->trafficVolume()->motorVolume();
			item->setGraphType(GraphicsNodeItem::MotorVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::NonMotorVolume:
			volume = tmpNodeData->trafficVolume()->nonMotorVolume();
			item->setGraphType(GraphicsNodeItem::NonMotorVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::CarVolume:
			volume = tmpNodeData->trafficVolume()->carVolume();
			item->setGraphType(GraphicsNodeItem::CarVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::BusVolume:
			volume = tmpNodeData->trafficVolume()->busVolume();
			item->setGraphType(GraphicsNodeItem::BusVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::MotorbikeVolume:
			volume = tmpNodeData->trafficVolume()->motorbikeVolume();
			item->setGraphType(GraphicsNodeItem::MotorbikeVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::TaxiVolume:
			volume = tmpNodeData->trafficVolume()->taxiVolume();
			item->setGraphType(GraphicsNodeItem::TaxiVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::TruckVolume:
			volume = tmpNodeData->trafficVolume()->truckVolume();
			item->setGraphType(GraphicsNodeItem::TruckVolumeGraph);
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
		
		item->setNodeData(tmpNodeData).setHaveBorder(mHaveBorderList.at(index))
			.setRadius(mSizeList.at(index)).setInnerColor(mInnerColorList.at(index))
			.setBorderColor(mBorderColorList.at(index)).setNodeItemType(GraphicsNodeItem::Restriction);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodeItemList << item;
		addItem(item);
	}
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge * tmpEdgeData;
	mEdgeNetItem = new GraphicsEdgeNetItem;
	mEdgeNetItem->setHaveBorder(mHaveBorderList.last()).setInnerColor(mInnerColorList.last())
		.setBorderColor(mBorderColorList.last()).setWidth(mSizeList.last());
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		mEdgeNetItem->addEdgeData(tmpEdgeData);
	}
	addItem(mEdgeNetItem);
}


void TrafficNodeVolumeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(mLabelTextList.at(0), LegendElement::THICK_DOT, mSizeList.at(0),
		mInnerColorList.at(0), mBorderColorList.at(0));
	elements << LegendElement(mLabelTextList.at(1), LegendElement::THICK_DOT, mSizeList.at(1),
		mInnerColorList.at(1), mBorderColorList.at(1));
	elements << LegendElement(mLabelTextList.at(2), LegendElement::THICK_DOT, mSizeList.at(2),
		mInnerColorList.at(2), mBorderColorList.at(2));
	elements << LegendElement(mLabelTextList.at(3), LegendElement::THICK_DOT, mSizeList.at(3),
		mInnerColorList.at(3), mBorderColorList.at(3));
	elements << LegendElement(mLabelTextList.at(4), LegendElement::THICK_DOT, mSizeList.at(4),
		mInnerColorList.at(4), mBorderColorList.at(4));
	elements << LegendElement(mLabelTextList.at(5), LegendElement::THICK_DOT,mSizeList.at(5),
		mInnerColorList.at(5), mBorderColorList.at(5));
	elements << LegendElement(mLabelTextList.at(6), LegendElement::THICK_LINE, mSizeList.at(6),
		mInnerColorList.at(6), mBorderColorList.at(6));

	mLegend = new Legend(elements);
	mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);
}

void TrafficNodeVolumeGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	GraphicsNodeItem * item;
	qreal volume;
	Node* tmpNodeData;
	int index;
	while (nodeItemIte.hasNext())
	{
		item = nodeItemIte.next();
		tmpNodeData = item->nodeData();
		switch (mVolumeType)
		{
		case TrafficNodeVolumeGraphicsScene::MotorVolume:
			volume = tmpNodeData->trafficVolume()->motorVolume();
			item->setGraphType(GraphicsNodeItem::MotorVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::NonMotorVolume:
			volume = tmpNodeData->trafficVolume()->nonMotorVolume();
			item->setGraphType(GraphicsNodeItem::NonMotorVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::CarVolume:
			volume = tmpNodeData->trafficVolume()->carVolume();
			item->setGraphType(GraphicsNodeItem::CarVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::BusVolume:
			volume = tmpNodeData->trafficVolume()->busVolume();
			item->setGraphType(GraphicsNodeItem::BusVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::MotorbikeVolume:
			volume = tmpNodeData->trafficVolume()->motorbikeVolume();
			item->setGraphType(GraphicsNodeItem::MotorbikeVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::TaxiVolume:
			volume = tmpNodeData->trafficVolume()->taxiVolume();
			item->setGraphType(GraphicsNodeItem::TaxiVolumeGraph);
			break;
		case TrafficNodeVolumeGraphicsScene::TruckVolume:
			volume = tmpNodeData->trafficVolume()->truckVolume();
			item->setGraphType(GraphicsNodeItem::TruckVolumeGraph);
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
		item->updateAttr(mInnerColorList.at(index), mBorderColorList.at(index), mSizeList.at(index),
			mHaveBorderList.at(index));
	}
	mEdgeNetItem->updateAttr(mInnerColorList.last(), mBorderColorList.last(),
		mSizeList.last(), mHaveBorderList.last());
	mLegend->updateAttr(mInnerColorList, mBorderColorList, mSizeList);
}
