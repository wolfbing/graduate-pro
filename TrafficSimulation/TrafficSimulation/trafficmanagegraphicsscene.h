#ifndef TRAFFICMANAGEGRAPHICSSCENE_H
#define TRAFFICMANAGEGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;

class TrafficManageGraphicsScene : public GraphicsScene
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
	void doSomething();
	void updateItems();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;

	// ªÊ÷∆ Ù–‘
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;
	
};

#endif // TRAFFICMANAGEGRAPHICSSCENE_H
