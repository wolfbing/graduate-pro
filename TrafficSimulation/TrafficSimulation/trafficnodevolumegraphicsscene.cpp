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
	: GraphicsScene(parent)
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

void TrafficNodeVolumeGraphicsScene::updateItems()
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

void TrafficNodeVolumeGraphicsScene::addLegend()
{
	QList<LegendElement> elements;
	elements << LegendElement(QString("<=100"), LegendElement::THICK_DOT, mNodeRadiusList.at(0),
		mNodeInnerColorList.at(0), mNodeBorderColorList.at(0));
	elements << LegendElement(QString("100-200"), LegendElement::THICK_DOT, mNodeRadiusList.at(1),
		mNodeInnerColorList.at(1), mNodeBorderColorList.at(1));
	elements << LegendElement(QString("200-500"), LegendElement::THICK_DOT, mNodeRadiusList.at(2),
		mNodeInnerColorList.at(2), mNodeBorderColorList.at(2));
	elements << LegendElement(QString("500-1000"), LegendElement::THICK_DOT, mNodeRadiusList.at(3),
		mNodeInnerColorList.at(3), mNodeBorderColorList.at(3));
	elements << LegendElement(QString("1000-2000"), LegendElement::THICK_DOT, mNodeRadiusList.at(4),
		mNodeInnerColorList.at(4), mNodeBorderColorList.at(4));
	elements << LegendElement(QString(">=2000"), LegendElement::THICK_DOT, mNodeRadiusList.at(5),
		mNodeInnerColorList.at(5), mNodeBorderColorList.at(5));
	elements << LegendElement(QStringLiteral("Â·¶Î"), LegendElement::THICK_LINE, mEdgeNetWidth,
		mEdgeNetInnerColor, mEdgeNetBorderColor);

	Legend * legend = new Legend(elements);
	LegendProxy * proxy = new LegendProxy;
	proxy->setWidget(legend);
	addItem(proxy);
}
