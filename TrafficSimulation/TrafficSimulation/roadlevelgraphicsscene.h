#ifndef ROADLEVELGRAPHICSSCENE_H
#define ROADLEVELGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class Edge;
class GraphicsEdgeItem;
class GraphicsEdgeNetItem;

class RoadLevelGraphicsScene :public RoadGraphicsScene
{
	Q_OBJECT

public:
	RoadLevelGraphicsScene(QObject *parent = 0);
	~RoadLevelGraphicsScene();

	void addItems();

private:
	void init();
	void addLegend();
	void updateItemsAttr();
	
private:

};

#endif // ROADLEVELGRAPHICSSCENE_H
