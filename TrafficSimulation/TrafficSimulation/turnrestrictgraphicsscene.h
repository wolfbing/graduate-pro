#ifndef TURNRESTRICTGRAPHICSSCENE_H
#define TURNRESTRICTGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsEdgeNetItem;
class GraphicsNodeItem;

class TurnRestrictGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	TurnRestrictGraphicsScene(QObject *parent=0);
	~TurnRestrictGraphicsScene();

	void addItems();

protected:
	void updateItems();
	void addLegend();
	void init();
	void doSomething();

private:
	QList<GraphicsNodeItem*> mNodeItemList;
	GraphicsEdgeNetItem* mEdgeNetItem;
	// ªÊ÷∆ Ù–‘
	QList<QColor> mNodeInnerColorList;
	QList<QColor> mNodeBorderColorList;
	QList<qreal> mNodeRadiusList;
	QList<bool> mNodeHaveBorderList;
	QColor mEdgeNetInnerColor;
	QColor mEdgeNetBorderColor;
	qreal mEdgeNetWidth;
	bool mEdgeNetHaveBorder;

};

#endif // TURNRESTRICTGRAPHICSSCENE_H
