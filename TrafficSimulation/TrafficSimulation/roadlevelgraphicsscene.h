#ifndef ROADLEVELGRAPHICSSCENE_H
#define ROADLEVELGRAPHICSSCENE_H

#include "graphicsscene.h"

class Edge;
class GraphicsEdgeItem;
class GraphicsEdgetNetItem;

class RoadLevelGraphicsScene :public GraphicsScene
{
	Q_OBJECT

public:
	RoadLevelGraphicsScene(QObject *parent = 0);
	~RoadLevelGraphicsScene();

	void addItems();

private:
	void updateItems();
	void doSomething(){};
	void init();
	void addLegend();
	
private:
	
	QList<GraphicsEdgeItem*> mEdgeList;
	QList<GraphicsEdgetNetItem*> mEdgeNetList;

	// 各种路的颜色和宽度
	// 几个list都严格按照道路等级的顺序
	QList<bool> mHaveBorderList;
	QList<QColor> mInnerColorList;
	QList<QColor> mBorderColorList;
	QList<qreal> mWidthList;
	QList<qreal> mZValueList;

};

#endif // ROADLEVELGRAPHICSSCENE_H
