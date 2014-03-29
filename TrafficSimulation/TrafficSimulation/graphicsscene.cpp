#include "graphicsscene.h"

GraphicsScene::GraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
	, mRatio(0.9)
	, mOffset(QPointF(0,0))
{
	setItemIndexMethod(QGraphicsScene::NoIndex);
	
}

GraphicsScene::~GraphicsScene()
{

}


void GraphicsScene::zoom( int step, QPointF hoverPos )
{
	if(mRatio==0.9 && step<=0)
		return;
	QPointF normPoint = sceneCoorToNormCoor(hoverPos);
	qreal minLen = shorterSceneRectSide();
	mRatio += 0.1 * step;
	if(mRatio<0.9)
		mRatio = 0.9;
	QPointF newScenePoint = 
		QPointF( normPoint.x() * minLen * mRatio, - normPoint.y()*minLen*mRatio);
	QPointF tmp = (hoverPos - newScenePoint)/(minLen*mRatio);
	mOffset = QPointF(tmp.x(), -tmp.y());
	updateItems();
	//moveItems();
}

void GraphicsScene::changeSceneRect( int w, int h )
{
	setSceneRect(-w/2.0, -h/2.0, w, h);
	updateItems();
	//moveItems();
}

QPointF GraphicsScene::normCoorToSceneCoor( QPointF point )
{
	qreal minLen = shorterSceneRectSide();
	qreal x = (point.x()+mOffset.x()) * minLen * mRatio;
	qreal y = -(point.y()+mOffset.y()) * minLen * mRatio;
	return QPointF(x, y);
}

void GraphicsScene::move( QPointF offset )
{ 
	qreal minLen = shorterSceneRectSide();
	QPointF normOffset(offset.x()/(minLen*mRatio), -offset.y()/(minLen*mRatio));
	mOffset += normOffset;
	updateItems();
	//moveItems();
}

qreal GraphicsScene::shorterSceneRectSide()
{
	QRectF rect = sceneRect(); 
	qreal minLen = qreal (rect.width()>rect.height() ? rect.height():rect.width());
	return minLen;
}

QPointF GraphicsScene::sceneCoorToNormCoor( QPointF point )
{
	qreal minLen = shorterSceneRectSide();
	qreal x = point.x()/(minLen*mRatio)-mOffset.x();
	qreal y = -point.y()/(minLen*mRatio)-mOffset.y();
	return QPointF(x, y);
}
