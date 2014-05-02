#include "trafficnodecapabilitygraphicsscene.h"
#include "graphicsnodeitem.h"
#include "node.h"
#include "graphicsedgenetitem.h"
#include "Capability.h"
#include "legend.h"
#include "legendproxy.h"
#include "legendelement.h"


TrafficNodeCapabilityGraphicsScene::TrafficNodeCapabilityGraphicsScene(QObject *parent)
	: CommonNodeGraphicsScene(parent)
{
	init();
	addLegend();
}

TrafficNodeCapabilityGraphicsScene::~TrafficNodeCapabilityGraphicsScene()
{

}

TrafficNodeCapabilityGraphicsScene& TrafficNodeCapabilityGraphicsScene::setCapabilityType(CapabilityType type)
{
	mCapabilityType = type;
	return *this;
}

void TrafficNodeCapabilityGraphicsScene::addItems()
{
	QListIterator<Node*> nodeIte(mNodeDataList);
	GraphicsNodeItem * item;
	qreal capability;
	Node* tmpNodeData;
	int index;
	while (nodeIte.hasNext())
	{
		tmpNodeData = nodeIte.next();
		item = new GraphicsNodeItem;

		switch (mCapabilityType)
		{
		case TrafficNodeCapabilityGraphicsScene::MotorCapability:
			capability = tmpNodeData->trafficCapability()->motorCapability();
			item->setGraphType(GraphicsNodeItem::MotorVolumeGraph);
			break;
		case TrafficNodeCapabilityGraphicsScene::NonMotorCapability:
			capability = tmpNodeData->trafficCapability()->nonMotorCapability();
			item->setGraphType(GraphicsNodeItem::NonMotorVolumeGraph);
			break;
		default:
			break;
		}
		if(capability<=0.40)
			index = 0;
		else if(capability<=0.60)
			index = 1;
		else if(capability<=0.75)
			index = 2;
		else if(capability<=0.90)
			index = 3;
		else if(capability<=1.00)
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

void TrafficNodeCapabilityGraphicsScene::init()
{
	mBorderColorList << QColor() << QColor() << QColor() << QColor() << QColor() << QColor() <<  QColor(203,168,87);
	mInnerColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40) << QColor(253,206,102);
	mSizeList << 4 << 4 << 4 << 4 << 4 << 4 << 4;
	mHaveBorderList << true << true << true << true << true << true << true ;
	mLabelTextList << "<=0.40" << "0.40-0.60" << "0.60-0.75" << "0.75-0.90"
		<< "0.90-1.00" << ">=1.00" << QStringLiteral("Â·¶Î");
}

void TrafficNodeCapabilityGraphicsScene::addLegend()
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
	elements << LegendElement(mLabelTextList.at(5), LegendElement::THICK_DOT, mSizeList.at(5),
		mInnerColorList.at(5), mBorderColorList.at(5));
	elements << LegendElement(mLabelTextList.at(6), LegendElement::THICK_LINE, mSizeList.at(6),
		mInnerColorList.at(6), mBorderColorList.at(6));
	mLegend = new Legend(elements);
	mLegendProxy = new LegendProxy;
	mLegendProxy->setWidget(mLegend);
	addItem(mLegendProxy);
}

void TrafficNodeCapabilityGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsNodeItem*> itemIte(mNodeItemList);
	GraphicsNodeItem * item;
	qreal capability;
	Node* tmpNodeData;
	int index;

	while (itemIte.hasNext())
	{
		item = itemIte.next();
		tmpNodeData = item->nodeData();
		switch (mCapabilityType)
		{
		case TrafficNodeCapabilityGraphicsScene::MotorCapability:
			capability = tmpNodeData->trafficCapability()->motorCapability();
			item->setGraphType(GraphicsNodeItem::MotorVolumeGraph);
			break;
		case TrafficNodeCapabilityGraphicsScene::NonMotorCapability:
			capability = tmpNodeData->trafficCapability()->nonMotorCapability();
			item->setGraphType(GraphicsNodeItem::NonMotorVolumeGraph);
			break;
		default:
			break;
		}
		if(capability<=0.40)
			index = 0;
		else if(capability<=0.60)
			index = 1;
		else if(capability<=0.75)
			index = 2;
		else if(capability<=0.90)
			index = 3;
		else if(capability<=1.00)
			index = 4;
		else
			index = 5;
		item->updateAttr(mInnerColorList.at(index), mBorderColorList.at(index), 
			mSizeList.at(index), mHaveBorderList.at(index));

	}
	mEdgeNetItem->updateAttr(mInnerColorList.last(), mBorderColorList.last(),
		mSizeList.last(), mHaveBorderList.last());
	mLegend->updateAttr(mInnerColorList, mBorderColorList, mSizeList);
}


