#include "nodegraphicsscene.h"
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	QList<NodeWithCoorNo>* nodeList = mDbAdapter.loadNormNodesWithNo();
	QList<ConnWithNoPair>* connList = mDbAdapter.loadConnsWithNoPair();
	QHash<int, GraphicsNodeItem*> hash;
	QListIterator<NodeWithCoorNo> ite(*nodeList);
	mNodes = QList<GraphicsNodeItem*>();
	NodeWithCoorNo node;
	GraphicsNodeItem* nodeItem;
	while (ite.hasNext())
	{
		node = ite.next();
		nodeItem = new GraphicsNodeItem(node.mCoor);
		nodeItem->setNo(node.mNo);
		mNodes << nodeItem;
		hash.insert(nodeItem->no(), nodeItem);
		addItem(nodeItem);
	}
	QListIterator<ConnWithNoPair> connIte(*connList);
	ConnWithNoPair tmpConn;
	mEdgeNet = new GraphicsEdgetNetItem;
	while (connIte.hasNext())
	{
		tmpConn = connIte.next();
		mEdgeNet->addEdge(Edge(hash.value(tmpConn.node1), hash.value(tmpConn.node2)));

	}
	addItem(mEdgeNet);

	delete nodeList;
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
		newPos = normCoorToSceneCoor(item->normPos());
		item->setPos(newPos);
	}
	mEdgeNet->advance();
}

