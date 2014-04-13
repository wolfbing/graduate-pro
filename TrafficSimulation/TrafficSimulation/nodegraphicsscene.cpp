#include "nodegraphicsscene.h"
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "graphicsnodenotextitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{		

	init();

	addLegend();
	
	

}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

void NodeGraphicsScene::updateItems()
{
	GraphicsScene::updateItems();
	QListIterator<GraphicsNodeItem*> ite(mNodes);
	GraphicsNodeItem* item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->setPos(item->nodeData()->sceneCoor());
	}
	mEdgeNet->advance();
	checkNoTextVisible();
}

void NodeGraphicsScene::checkNoTextVisible()
{
	QListIterator<GraphicsNodeNoTextItem*> ite(mNodeNoTextItemList);
	GraphicsNodeNoTextItem * item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->updateVisible();
	}

}


void NodeGraphicsScene::doSomething()
{
	checkNoTextVisible();
}

void NodeGraphicsScene::addItems()
{
	///// 添加节点和节点编号
	QListIterator<Node*> nodeIte(mNodeDataList);
	Node * tmpNodeData;
	GraphicsNodeItem* nodeItem;
	GraphicsNodeNoTextItem* nodeNoTextItem;
	QHash<Node*, GraphicsNodeNoTextItem*> nodeNoTextHash;
	while (nodeIte.hasNext())
	{
		tmpNodeData = nodeIte.next();
		nodeItem = new GraphicsNodeItem;
		nodeItem->setNodeData(tmpNodeData).setInnerColor(mNodeInnerColor).setBorderColor(mNodeBorderColor)
			.setHaveBorder(mNodeHaveBorder).setRadius(mNodeRadius);
		nodeNoTextItem = new GraphicsNodeNoTextItem(nodeItem);
		nodeNoTextItem->setNodeData(tmpNodeData);
		connect(nodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(nodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodes << nodeItem;
		mNodeNoTextItemList << nodeNoTextItem;
		addItem(nodeItem);
		addItem(nodeNoTextItem);
		nodeNoTextHash.insert(tmpNodeData, nodeNoTextItem);
	} ////  添加节点和编号完成
	///// 添加edgenet
	Edge * tmpEdgeData;
	mEdgeNet = new GraphicsEdgeNetItem;
	mEdgeNet->setHaveBorder(mEdgeNetHaveBorder).setBorderColor(mEdgeNetBorderColor).setInnerColor(mEdgeNetInnerColor)
		.setWidth(mEdgeNetWidth);
	QListIterator<Edge*> edgeIte(mEdgeDataList);
	Node * tmpNode1, *tmpNode2;
	GraphicsNodeNoTextItem * tmpNodeNoTextItem1, *tmpNodeNoTextItem2;
	while (edgeIte.hasNext())
	{
		tmpEdgeData = edgeIte.next();
		mEdgeNet->addEdgeData(tmpEdgeData);
		tmpNode1 = tmpEdgeData->sourceNode();
		tmpNode2 = tmpEdgeData->destNode();
		tmpNodeNoTextItem1 = nodeNoTextHash.value(tmpNode1);
		tmpNodeNoTextItem2 = nodeNoTextHash.value(tmpNode2);
		tmpNodeNoTextItem1->updateNeighbour(tmpNodeNoTextItem2);
		tmpNodeNoTextItem2->updateNeighbour(tmpNodeNoTextItem1);

	}
	addItem(mEdgeNet);  ////////// 添加edgenet完成

}


void NodeGraphicsScene::init()
{
	mNodeRadius = 4.0;
	mNodeBorderColor = QColor(38,0,0);
	mNodeInnerColor = QColor(178,73,77);
	mNodeHaveBorder = true;

	mEdgeNetHaveBorder = true;
	mEdgeNetBorderColor = QColor(203,168,87);
	mEdgeNetInnerColor = QColor(253,206,102);
	mEdgeNetWidth = 4.0;
}

void NodeGraphicsScene::addLegend()
{
	// 添加图例
	QList<LegendElement> legendList;
	legendList << LegendElement(QStringLiteral("节点"), LegendElement::THICK_DOT, mNodeRadius, 
		mNodeInnerColor, mNodeBorderColor );
	legendList << LegendElement(QStringLiteral("路段"), LegendElement::THICK_LINE, mEdgeNetWidth,
		mEdgeNetInnerColor, mEdgeNetBorderColor );
	Legend * legend = new Legend(legendList);
	LegendProxy* proxy = new LegendProxy(legend);
	addItem(proxy);
}

