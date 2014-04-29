#ifndef SPEEDGRAPHICSSCENE_H
#define SPEEDGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsSideLineItem;

class SpeedGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	SpeedGraphicsScene(QObject *parent=0);
	~SpeedGraphicsScene();

	void addItems();

protected:
	void init();
	void addLegend();
	void updateItems();

private:
	QList<GraphicsSideLineItem*> mSideLineItemList;
	// ªÊ÷∆ Ù–‘
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;


	
};

#endif // SPEEDGRAPHICSSCENE_H
