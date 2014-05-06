#ifndef JUNCTIONTYPEGRAPHICSSCENE_H
#define JUNCTIONTYPEGRAPHICSSCENE_H

#include "commonnodegraphicsscene.h"

class GraphicsEdgeNetItem;
class GraphicsNodeItem;

class JunctionTypeGraphicsScene : public CommonNodeGraphicsScene
{
	Q_OBJECT

public:
	JunctionTypeGraphicsScene(QObject *parent=0);
	~JunctionTypeGraphicsScene();

	void addItems();

protected:
	void updateItemsAttr();

private:
	void init();
	void addLegend();


private:
	
};

#endif // JUNCTIONTYPEGRAPHICSSCENE_H
