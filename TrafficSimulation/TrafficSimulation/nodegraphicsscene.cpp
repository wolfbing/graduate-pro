#include "nodegraphicsscene.h"
#include <QtWidgets>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
	
{
	mPointList = mDbAdapter.loadNormNodesWithNo();
	mConnList = mDbAdapter.loadNormConns();
	mItemList = QList<QGraphicsItem*>();
	//mConnItemList = QList<QGraphicsItem*>();
	updateItems();
}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

void NodeGraphicsScene::updateItems()
{
	clear();
	QListIterator<NodeWithCoorNo> nodeIte(*mPointList);
	QPointF normPoint;
	QPointF scenePoint;
	mItemList.clear();
	while (nodeIte.hasNext())
	{
		normPoint = nodeIte.next().mCoor;
		scenePoint = normCoorToSceneCoor(normPoint);
		QGraphicsItem* item = new QGraphicsEllipseItem(scenePoint.x()-3, scenePoint.y()-3, 6, 6);
		item->setData(1, normPoint.x());
		item->setData(2, normPoint.y());
		item->setData(3, scenePoint.x());
		item->setData(4, scenePoint.y());
		addItem(item);
		mItemList.append(item);
	}
	QListIterator<ConnWithCoorPair> connIte(*mConnList);
	while (connIte.hasNext())
	{
		ConnWithCoorPair conn = connIte.next();
		QPointF normFP = conn.mCoorPair.first;
		QPointF normSP = conn.mCoorPair.second;
		QPointF sceneFP = normCoorToSceneCoor(normFP);
		QPointF sceneSP = normCoorToSceneCoor(normSP);
		QGraphicsLineItem* item = new QGraphicsLineItem(QLineF(sceneFP, sceneSP));
		addItem(item);
		mItemList.append(item);
	}

}

void NodeGraphicsScene::moveItems()
{
	QListIterator<QGraphicsItem*> ite(mItemList);
	QGraphicsItem* item;
	QPointF newScenePos, scenePos, delta;
	while(ite.hasNext())
	{
		item = ite.next();
		newScenePos = normCoorToSceneCoor(QPointF(item->data(1).toReal(),item->data(2).toReal()));
		scenePos = QPointF(item->data(3).toReal(), item->data(4).toReal());
		item->setData(3, newScenePos.x());
		item->setData(4, newScenePos.y());
		delta = newScenePos - scenePos;
		item->moveBy(delta.x(), delta.y());

	}
}

