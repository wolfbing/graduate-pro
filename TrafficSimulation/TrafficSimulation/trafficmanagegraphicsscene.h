#ifndef TRAFFICMANAGEGRAPHICSSCENE_H
#define TRAFFICMANAGEGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class GraphicsSideLineItem;

class TrafficManageGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	TrafficManageGraphicsScene(QObject *parent=0);
	~TrafficManageGraphicsScene();

public:
	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:
	
};

#endif // TRAFFICMANAGEGRAPHICSSCENE_H
