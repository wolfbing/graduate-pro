#ifndef ROADTYPEGRAPHICSSCENE_H
#define ROADTYPEGRAPHICSSCENE_H

#include <QGraphicsScene>
#include "graphicsscene.h"

class GraphicsSideLineItem;
class GraphicsEdgeItem;

class RoadTypeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	RoadTypeGraphicsScene(QObject *parent=0);
	~RoadTypeGraphicsScene();

	void addItems();

protected:
	void init();
	void updateItems();
	void addLegend();
	void doSomething();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;

	// ªÊ÷∆ Ù–‘
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;

	
};

#endif // ROADTYPEGRAPHICSSCENE_H
