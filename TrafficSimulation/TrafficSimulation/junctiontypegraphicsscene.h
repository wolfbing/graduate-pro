#ifndef JUNCTIONTYPEGRAPHICSSCENE_H
#define JUNCTIONTYPEGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsEdgeNetItem;
class GraphicsNodeItem;

class JunctionTypeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	JunctionTypeGraphicsScene(QObject *parent=0);
	~JunctionTypeGraphicsScene();

	void addItems();

private:
	void init();
	void updateItems();
	void addLegend();
	void doSomething();

private:
	GraphicsEdgeNetItem * mEdgeNetItem;
	QList<GraphicsNodeItem*> mNodeItemList;

	// ªÊÕº Ù–‘
	QList<QColor> mNodeInnerColorList;
	QList<QColor> mNodeBorderColorList;
	QList<qreal> mNodeRadiusList;
	QList<bool> mNodeHaveBorderList;

	QColor mEdgeNetInnerColor;
	QColor mEdgeNetBorderColor;
	bool mEdgeNetHaveBorder;
	qreal mEdgeNetWidth;
	
};

#endif // JUNCTIONTYPEGRAPHICSSCENE_H
