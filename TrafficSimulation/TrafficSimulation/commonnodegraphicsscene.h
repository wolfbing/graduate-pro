#ifndef COMMONNODEGRAPHICSSCENE_H
#define COMMONNODEGRAPHICSSCENE_H

#include "graphicsscene.h"

class GraphicsEdgeNetItem;
class GraphicsNodeItem;
class LegendProxy;
class Legend;

class CommonNodeGraphicsScene : public GraphicsScene
{
	Q_OBJECT

public:
	CommonNodeGraphicsScene(QObject *parent);
	~CommonNodeGraphicsScene();

	virtual void addItems()=0;

public slots:
	void config();

protected:
	virtual void init()=0;
	virtual void addLegend()=0;
	virtual void updateItems();
	virtual void updateItemsAttr(){};


protected:
	QList<GraphicsNodeItem*> mNodeItemList;
	GraphicsEdgeNetItem* mEdgeNetItem;
	// ªÊ÷∆ Ù–‘
	QList<QColor> mInnerColorList;
	QList<QColor> mBorderColorList;
	QList<qreal> mSizeList;
	QList<bool> mHaveBorderList;

	QList<QString> mLabelTextList;
	LegendProxy* mLegendProxy;
	Legend* mLegend;
	
};

#endif // COMMONNODEGRAPHICSSCENE_H
