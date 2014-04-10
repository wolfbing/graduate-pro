#ifndef BUSNUMGRAPHICSSCENE_H
#define BUSNUMGRAPHICSSCENE_H

#include <QObject>
#include "graphicsscene.h"
#include "graphicsbusedgeitem.h"

class Edge;
class Node;
class GraphicsEdgeItem;


class BusNumGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	BusNumGraphicsScene(QObject *parent = 0);
	~BusNumGraphicsScene();

	void addItems();

private:
	void updateItems();
	void doSomething();
	void init();
	void addLegend();
	
private:
	

private:
	QList<GraphicsBusEdgeItem*> mEdgeList;
	//// ªÊ÷∆ Ù–‘
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
};

#endif // BUSNUMGRAPHICSSCENE_H
