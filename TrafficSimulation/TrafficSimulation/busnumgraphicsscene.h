#ifndef BUSNUMGRAPHICSSCENE_H
#define BUSNUMGRAPHICSSCENE_H

#include <QObject>
#include "roadgraphicsscene.h"
#include "graphicsbusedgeitem.h"

class Edge;
class Node;
class GraphicsEdgeItem;


class BusNumGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	BusNumGraphicsScene(QObject *parent = 0);
	~BusNumGraphicsScene();

	void addItems();

private:
	void updateItemsAttr();
	void init();
	void addLegend();
	
private:
};

#endif // BUSNUMGRAPHICSSCENE_H
