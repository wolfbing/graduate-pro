#ifndef SPEEDGRAPHICSSCENE_H
#define SPEEDGRAPHICSSCENE_H

#include "roadgraphicsscene.h"

class GraphicsSideLineItem;

class SpeedGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	SpeedGraphicsScene(QObject *parent=0);
	~SpeedGraphicsScene();

	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:


	
};

#endif // SPEEDGRAPHICSSCENE_H
