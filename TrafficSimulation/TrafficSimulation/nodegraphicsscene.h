#ifndef NODEGRAPHICSSCENE_H
#define NODEGRAPHICSSCENE_H

#include "graphicsscene.h"
#include "node.h"
#include "DbAdapter.h"
#include <QGraphicsEllipseItem>
#include "conn.h"
#include "graphicsnodeitem.h"
#include "graphicsedgenetitem.h"
#include "graphicsnodenotextitem.h"

class NodeGraphicsScene : public GraphicsScene
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

	void init();
	void addLegend();

private:	
	QList<GraphicsNodeItem*> mNodes;
	GraphicsEdgetNetItem* mEdgeNet;	
	QList<GraphicsNodeNoTextItem*> mNodeNoTextItemList;

	// ªÊÕº Ù–‘
	qreal mNodeRadius;
	QColor mNodeInnerColor;
	QColor mNodeBorderColor;
	qreal mEdgeNetWidth;
	QColor mEdgeNetInnerColor;
	QColor mEdgeNetBorderColor;
	bool mNodeHaveBorder;
	bool mEdgeNetHaveBorder;

};

#endif // NODEGRAPHICSSCENE_H
