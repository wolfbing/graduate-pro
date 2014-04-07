#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include "graphicsscene.h"
#include "node.h"
#include "DbAdapter.h"
#include <QGraphicsEllipseItem>
#include "conn.h"
#include "graphicsnodeitem.h"
#include "graphicsedgenetitem.h"

class NodeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	NodeGraphicsScene(QObject *parent = 0);
	~NodeGraphicsScene();

	int nodeNum() const;
	int edgeNum() const;



private:
	void updateItems();
	void doSomething();
	void checkNoTextVisible();

private:	
	DbAdapter mDbAdapter;
	QList<Node*> mNodeDataList;
	QList<GraphicsNodeItem*> mNodes;
	GraphicsEdgetNetItem* mEdgeNet;
	int mEdgeNum;
	

};

#endif // NODEGRAPHICSSCENE_H
