#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include "commonnodegraphicsscene.h"
#include "node.h"
#include "DbAdapter.h"
#include <QGraphicsEllipseItem>
#include "conn.h"
#include "graphicsnodeitem.h"
#include "graphicsedgenetitem.h"
#include "graphicsnodenotextitem.h"

class NodeGraphicsScene : public CommonNodeGraphicsScene
{
	Q_OBJECT

public:
	NodeGraphicsScene(QObject *parent = 0);
	~NodeGraphicsScene();

	void addItems();

private:
	void updateItems();
	void doSomething();
	void checkNoTextVisible();
	void updateItemsAttr();


	void init();
	void addLegend();

private:	
	QList<GraphicsNodeNoTextItem*> mNodeNoTextItemList;


};

#endif // NODEGRAPHICSSCENE_H
