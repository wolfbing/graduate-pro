#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include "DbAdapter.h"

class GraphicsScene : public QGraphicsScene
{
	Q_OBJECT

public:
	GraphicsScene(QObject *parent = 0);
	~GraphicsScene();

public slots:	
	void changeSceneRect(int w, int h);
	void zoom(int step, QPointF hoverPos);
	void move(QPointF offset);

protected:
	virtual void updateItems()=0;
	virtual void moveItems()=0;
	QPointF normCoorToSceneCoor(QPointF);
	QPointF sceneCoorToNormCoor(QPointF);
	qreal shorterSceneRectSide(); // 返回sceneRect中较短的边

protected:
	DbAdapter mDbAdapter;

private:
	qreal mRatio;
	QPointF mOffset;

};

#endif // GRAPHICSSCENE_H
