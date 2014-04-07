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
	mNodeDataList = mDbAdapter.loadNormNodesWithNo();
	QList<ConnWithNoPair>* connList = mDbAdapter.loadConnsWithNoPair();
	QHash<int, Node*> hash;
	QListIterator<Node*> ite(mNodeDataList);
	mNodes = QList<GraphicsNodeItem*>();
	Node * tmpNodeData;
	GraphicsNodeItem* nodeItem;
	GraphicsNodeNoTextItem* nodeNoTextItem;
	while (ite.hasNext())
	{
		tmpNodeData = ite.next();
		nodeItem = new GraphicsNodeItem;
		nodeItem->setNodeData(tmpNodeData);
		nodeNoTextItem = new GraphicsNodeNoTextItem(nodeItem);
		connect(nodeItem, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(nodeItem, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus() ) );
		mNodes << nodeItem;
		hash.insert(nodeItem->nodeData()->no(), tmpNodeData);
		addItem(nodeItem);
		addItem(nodeNoTextItem);
	}
	QListIterator<ConnWithNoPair> connIte(*connList);
	ConnWithNoPair tmpConn;
	mEdgeNet = new GraphicsEdgetNetItem;
	while (connIte.hasNext())
	{
		tmpConn = connIte.next();
		Edge * tmpEdgeData = new Edge;
		tmpEdgeData->setSourceNode(hash.value(tmpConn.node1));
		tmpEdgeData->setDestNode(hash.value(tmpConn.node2));
		mEdgeNet->addEdgeData(tmpEdgeData);
	}
	addItem(mEdgeNet);
	mEdgeNum = connList->size();

	
	// 添加图例
	QList<LegendElement> legendList;
	GraphicsNodeItem* tmpNode = mNodes.at(0);
	legendList << LegendElement(QStringLiteral("节点"), LegendElement::THICK_DOT, tmpNode->radius(), 
		tmpNode->innerColor(), tmpNode->borderColor() );
	legendList << LegendElement(QStringLiteral("路段"), LegendElement::THICK_LINE, mEdgeNet->edgeWidth(),
		mEdgeNet->innerColor(), mEdgeNet->borderColor() );
	Legend * legend = new Legend(legendList);
	LegendProxy* proxy = new LegendProxy(legend);
	addItem(proxy);
	

	delete connList;

}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

void NodeGraphicsScene::updateItems()
{
	QListIterator<GraphicsNodeItem*> ite(mNodes);
	GraphicsNodeItem* item;
	QPointF newPos ;
	while (ite.hasNext())
	{
		item = ite.next();
		newPos = normCoorToSceneCoor(item->nodeData()->coor());
		item->nodeData()->setSceneCoor(newPos);
		item->setPos(newPos);
	}
	mEdgeNet->advance();
}

void NodeGraphicsScene::checkNoTextVisible()
{
	QListIterator<GraphicsNodeItem*> ite(mNodes);
	GraphicsNodeItem * item;
	while (ite.hasNext())
	{
		item = ite.next();
		item->checkNoItemVisible();
	}

}

int NodeGraphicsScene::nodeNum() const
{
	return mNodes.size();
}

int NodeGraphicsScene::edgeNum() const
{
	return mEdgeNum;
}

void NodeGraphicsScene::doSomething()
{
	checkNoTextVisible();
}

