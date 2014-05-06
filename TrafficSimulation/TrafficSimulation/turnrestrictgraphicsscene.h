#ifndef TURNRESTRICTGRAPHICSSCENE_H
#define TURNRESTRICTGRAPHICSSCENE_H

#include "commonnodegraphicsscene.h"

class GraphicsEdgeNetItem;
class GraphicsNodeItem;

class TurnRestrictGraphicsScene : public CommonNodeGraphicsScene
{
	Q_OBJECT

public:
	TurnRestrictGraphicsScene(QObject *parent=0);
	~TurnRestrictGraphicsScene();

	void addItems();

protected:
	void addLegend();
	void init();
	void updateItemsAttr();

private:
	

};

#endif // TURNRESTRICTGRAPHICSSCENE_H
