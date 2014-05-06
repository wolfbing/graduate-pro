#ifndef ROADTYPEGRAPHICSSCENE_H
#define ROADTYPEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "roadgraphicsscene.h"

class GraphicsSideLineItem;
class GraphicsEdgeItem;

class RoadTypeGraphicsScene : public RoadGraphicsScene
{
	Q_OBJECT

public:
	RoadTypeGraphicsScene(QObject *parent=0);
	~RoadTypeGraphicsScene();

	void addItems();

protected:
	void init();
	void addLegend();
	void updateItemsAttr();

private:

	
};

#endif // ROADTYPEGRAPHICSSCENE_H
