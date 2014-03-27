#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include "graphicsscene.h"
#include "node.h"
#include "DbAdapter.h"
#include <QGraphicsEllipseItem>
#include "conn.h"

class NodeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	NodeGraphicsScene(QObject *parent = 0);
	~NodeGraphicsScene();


private:
	void updateItems();
	void moveItems();

private:	
	QList<NodeWithCoorNo>* mPointList;
	QList<ConnWithCoorPair>* mConnList;
	QList<QGraphicsItem*> mItemList;
	//QList<QGraphicsItem*> mConnItemList;

};

#endif // NODEGRAPHICSSCENE_H
