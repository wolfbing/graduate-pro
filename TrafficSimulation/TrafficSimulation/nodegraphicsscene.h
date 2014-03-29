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


private:
	void updateItems();

private:	
	DbAdapter mDbAdapter;
	QList<GraphicsNodeItem*> mNodes;
	GraphicsEdgetNetItem* mEdgeNet;
	

};

#endif // NODEGRAPHICSSCENE_H
