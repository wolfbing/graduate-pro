#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>

/*
Base class of other XXXGraphicsScene

Pure virtual functions:
	- init() - should not be public
	- addItems() - must be public
	- updateItems() - should not be public
	- addLegend() - should not be public
	- doSomething() - should not be public

The specific XXXGraphicsScene class that inherits from GraphicsScene just need to 
design their scene and implement the pure virtual functions. Then, the scene will 
be completed with translate,scale,print functions(implemented by GraphicsScene class).

Before you use a XXXGraphcisScene object, you should setNodeDataList(), setEdgeDataList(),
and addItems() emplicitly. Just like this:
	<code>
	XXXGraphicsScene scene;
	scene.setNodeDataList(nodelist).setEdgeDataList(edgelist).addItems();
	</code>

*/

class Node;
class Edge;

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(QObject *parent = 0);
	~GraphicsScene();

	int edgeNum() const ;
	int nodeNum() const ;

	GraphicsScene & setNodeDataList(QList<Node*>);
	GraphicsScene & setEdgeDataList(QList<Edge*>);

	virtual void addItems()=0;

public slots:	
	void changeSceneRect(int w, int h);
	void zoom(int step, QPointF hoverPos);
	void move(QPointF offset);

signals:
	void sendMsgToStatus(QString);
	void clearMsgFromStatus();

protected:
	virtual void init()=0;
	virtual void updateItems();
	virtual void addLegend()=0;
	QPointF normCoorToSceneCoor(QPointF);
	QPointF sceneCoorToNormCoor(QPointF);
	qreal shorterSceneRectSide(); // 返回sceneRect中较短的边

	virtual void doSomething()=0;
	// 重载
	void drawBackground(QPainter *painter, const QRectF &rect);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

protected:
	QList<Node*> mNodeDataList;
	QList<Edge*> mEdgeDataList;

private:
	qreal mRatio;
	QPointF mOffset;

	QColor mBackColor;

	bool mLeftBtnPressed;

};

#endif // GRAPHICSSCENE_H
