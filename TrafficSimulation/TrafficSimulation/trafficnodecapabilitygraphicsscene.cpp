#include "trafficnodecapabilitygraphicsscene.h"
#include "graphicsnodeitem.h"
#include "node.h"
#include "graphicsedgenetitem.h"
#include "Capability.h"
#include "legend.h"
#include "legendproxy.h"
#include "legendelement.h"


TrafficNodeCapabilityGraphicsScene::TrafficNodeCapabilityGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
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

		item->setNodeData(tmpNodeData).setHaveBorder(mNodeHaveBorderList.at(index))
			.setRadius(mNodeRadiusList.at(index)).setInnerColor(mNodeInnerColorList.at(index))
			.setBorderColor(mNodeBorderColorList.at(index)).setNodeItemType(GraphicsNodeItem::Restriction);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodeItemList << item;
		addItem(item);
	}
	QListIterator<Edge*> edgeDataIte(mEdgeDataList);
	Edge * tmpEdgeData;
	mEdgeNetItem = new GraphicsEdgeNetItem;
	mEdgeNetItem->setHaveBorder(mEdgeNetHaveBorder).setInnerColor(mEdgeNetInnerColor)
		.setBorderColor(mEdgeNetBorderColor).setWidth(mEdgeNetWidth);
	while (edgeDataIte.hasNext())
	{
		tmpEdgeData = edgeDataIte.next();
		mEdgeNetItem->addEdgeData(tmpEdgeData);
	}
	addItem(mEdgeNetItem);
}

void TrafficNodeCapabilityGraphicsScene::init()
{
	mNodeBorderColorList << QColor() << QColor() << QColor() << QColor() << QColor() << QColor();
	mNodeInnerColorList << QColor(158,158,158) << QColor(0,122,204) << QColor(50,158,28) 
		<<  QColor(230,204,58) << QColor(240,129,0) << QColor(223,35,40);
	mNodeRadiusList << 4 << 4 << 4 << 4 << 4 << 4;
	mNodeHaveBorderList << true << true << true << true << true << true ;
	mEdgeNetBorderColor =  QColor(203,168,87);
	mEdgeNetHaveBorder = true;
	mEdgeNetWidth = 4.0;
	mEdgeNetInnerColor = QColor(253,206,102);
}

void TrafficNodeCapabilityGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QString("<=0.40"), LegendElement::THICK_DOT, mNodeRadiusList.at(0),
		mNodeInnerColorList.at(0), mNodeBorderColorList.at(0));
	elements << LegendElement(QString("0.40-0.60"), LegendElement::THICK_DOT, mNodeRadiusList.at(1),
		mNodeInnerColorList.at(1), mNodeBorderColorList.at(1));
	elements << LegendElement(QString("0.60-0.75"), LegendElement::THICK_DOT, mNodeRadiusList.at(2),
		mNodeInnerColorList.at(2), mNodeBorderColorList.at(2));
	elements << LegendElement(QString("0.75-0.90"), LegendElement::THICK_DOT, mNodeRadiusList.at(3),
		mNodeInnerColorList.at(3), mNodeBorderColorList.at(3));
	elements << LegendElement(QString("0.90-1.00"), LegendElement::THICK_DOT, mNodeRadiusList.at(4),
		mNodeInnerColorList.at(4), mNodeBorderColorList.at(4));
	elements << LegendElement(QString(">=1.00"), LegendElement::THICK_DOT, mNodeRadiusList.at(5),
		mNodeInnerColorList.at(5), mNodeBorderColorList.at(5));
	elements << LegendElement(QStringLiteral("Â·¶Î"), LegendElement::THICK_LINE, mEdgeNetWidth,
		mEdgeNetInnerColor, mEdgeNetBorderColor);

	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);
}

void TrafficNodeCapabilityGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsNodeItem*> nodeItemIte(mNodeItemList);
	GraphicsNodeItem* tmpNodeItem;
	while (nodeItemIte.hasNext())
	{
		tmpNodeItem = nodeItemIte.next();
		tmpNodeItem->setPos(tmpNodeItem->nodeData()->sceneCoor());

	}
	mEdgeNetItem->advance();
}
