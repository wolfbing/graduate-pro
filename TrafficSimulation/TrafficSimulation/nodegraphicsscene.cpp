#include "nodegraphicsscene.h"
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include "graphicsnodenotextitem.h"
#include "legend.h"
#include "legendelement.h"
#include "legendproxy.h"

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
	: CommonNodeGraphicsScene(parent)
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
	QListIterator<GraphicsNodeItem*> ite(mNodeItemList);
	GraphicsNodeItem* item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->setPos(item->nodeData()->sceneCoor());
	}
	mEdgeNetItem->advance();
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
		nodeItem->setNodeData(tmpNodeData).setInnerColor(mInnerColorList.at(0)).setBorderColor(mBorderColorList.at(0))
			.setHaveBorder(mHaveBorderList.at(0)).setRadius(mSizeList.at(0));
		nodeNoTextItem = new GraphicsNodeNoTextItem(nodeItem);
		nodeNoTextItem->setNodeData(tmpNodeData);
		connect(nodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(nodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodeItemList << nodeItem;
		mNodeNoTextItemList << nodeNoTextItem;
		addItem(nodeItem);
		addItem(nodeNoTextItem);
		nodeNoTextHash.insert(tmpNodeData, nodeNoTextItem);
	} ////  添加节点和编号完成
	///// 添加edgenet
	Edge * tmpEdgeData;
	mEdgeNetItem = new GraphicsEdgeNetItem;
	mEdgeNetItem->setHaveBorder(mHaveBorderList.last()).setBorderColor(mBorderColorList.last()).setInnerColor(mInnerColorList.last())
		.setWidth(mSizeList.last());
	QListIterator<Edge*> edgeIte(mEdgeDataList);
	Node * tmpNode1, *tmpNode2;
	GraphicsNodeNoTextItem * tmpNodeNoTextItem1, *tmpNodeNoTextItem2;
	while (edgeIte.hasNext())
	{
		tmpEdgeData = edgeIte.next();
		mEdgeNetItem->addEdgeData(tmpEdgeData);
		tmpNode1 = tmpEdgeData->sourceNode();
		tmpNode2 = tmpEdgeData->destNode();
		tmpNodeNoTextItem1 = nodeNoTextHash.value(tmpNode1);
		tmpNodeNoTextItem2 = nodeNoTextHash.value(tmpNode2);
		tmpNodeNoTextItem1->updateNeighbour(tmpNodeNoTextItem2);
		tmpNodeNoTextItem2->updateNeighbour(tmpNodeNoTextItem1);

	}
	addItem(mEdgeNetItem);  ////////// 添加edgenet完成

}


void NodeGraphicsScene::init()
{
	mSizeList << 4.0 << 4.0;
	mInnerColorList <<  QColor(178,73,77) << QColor(253,206,102);
	mBorderColorList << QColor(38,0,0) << QColor(203,168,87);
	mHaveBorderList << true << true;
	mLabelTextList << QStringLiteral("节点") << QStringLiteral("路段");

}

void NodeGraphicsScene::addLegend()
{
	// 添加图例
	QList<LegendElement> legendList;
	legendList << LegendElement(mLabelTextList.at(0), LegendElement::THICK_DOT, mSizeList.at(0), 
		mInnerColorList.at(0), mBorderColorList.at(0) );
	legendList << LegendElement(mLabelTextList.at(1), LegendElement::THICK_LINE, mSizeList.at(1),
		mInnerColorList.at(1), mBorderColorList.at(1) );
	mLegend = new Legend(legendList);
	mLegendProxy = new LegendProxy(mLegend);
	addItem(mLegendProxy);
}

void NodeGraphicsScene::updateItemsAttr()
{
	QListIterator<GraphicsNodeItem*> nodeIte(mNodeItemList);
	Node * tmpNodeData;
	GraphicsNodeItem* nodeItem;
	int index = 0;
	while (nodeIte.hasNext())
	{
		nodeItem = nodeIte.next();
		tmpNodeData = nodeItem->nodeData();
		nodeItem->updateAttr(mInnerColorList.at(index), mBorderColorList.at(index),
			mSizeList.at(index), mHaveBorderList.at(index));
	}
	mEdgeNetItem->updateAttr(mInnerColorList.last(), mBorderColorList.last(), mSizeList.last(), mHaveBorderList.last());
	mLegend->updateAttr(mInnerColorList, mBorderColorList, mSizeList);
	//mLegendProxy->newUpdateAttr(mInnerColorList, mBorderColorList, mSizeList);
}

