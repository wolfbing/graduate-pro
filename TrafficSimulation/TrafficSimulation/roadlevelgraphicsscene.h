#ifndef ROADLEVELGRAPHICSSCENE_H
#define ROADLEVELGRAPHICSSCENE_H

#include "graphicsscene.h"

class Edge;
class GraphicsEdgeItem;

class RoadLevelGraphicsScene :public GraphicsScene
{
	Q_OBJECT

public:
	RoadLevelGraphicsScene(QObject *parent = 0);
	~RoadLevelGraphicsScene();

	int edgeNum(){return 100;};
	int nodeNum(){return 100;};

private:
	void updateItems();
	void doSomething(){};
	void init();

private:
	
	QList<GraphicsEdgeItem*> mEdgeList;
	QList<Node*> mNodeList;


	// 各种路的颜色和宽度
	QColor mColor0, mColor1, mColor2, mColor3, mColor4, mColor5, mColor6,
		mOutColor0, mOutColor1, mOutColor2, mOutColor3, mOutColor6;
	int mWidth0, mWidth1, mWidth2, mWidth3, mWidth4, mWidth5, mWidth6;

};

#endif // ROADLEVELGRAPHICSSCENE_H
