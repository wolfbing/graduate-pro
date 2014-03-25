#include "nodegraphicsscene.h"
#include <QtWidgets>

NodeGraphicsScene::NodeGraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
	, mRatio(0.9)
	, mOffset(QPointF(0,0))
{
	mPointList = mDbAdapter.loadNodes();
	
}

NodeGraphicsScene::~NodeGraphicsScene()
{

}

void NodeGraphicsScene::updateItems()
{
	clear();
	QListIterator<QPointF> ite(*mPointList);
	QPointF normPoint;
	QPointF scenePoint;
	while (ite.hasNext())
	{
		normPoint = ite.next();
		scenePoint = normCoorToSceneCoor(normPoint);
		addItem(new QGraphicsEllipseItem(scenePoint.x()-3, scenePoint.y()-3, 6, 6));
	}

}

void NodeGraphicsScene::zoom( int step, QPointF hoverPos )
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
}

void NodeGraphicsScene::changeSceneRect( int w, int h )
{
	setSceneRect(-w/2.0, -h/2.0, w, h);
	updateItems();
}

QPointF NodeGraphicsScene::normCoorToSceneCoor( QPointF point )
{
	qreal minLen = shorterSceneRectSide();
	qreal x = (point.x()+mOffset.x()) * minLen * mRatio;
	qreal y = -(point.y()+mOffset.y()) * minLen * mRatio;
	return QPointF(x, y);
}

void NodeGraphicsScene::move( QPointF offset )
{ 
	qreal minLen = shorterSceneRectSide();
	QPointF normOffset(offset.x()/(minLen*mRatio), -offset.y()/(minLen*mRatio));
	mOffset += normOffset;
	updateItems();
}

qreal NodeGraphicsScene::shorterSceneRectSide()
{
	QRectF rect = sceneRect(); 
	qreal minLen = qreal (rect.width()>rect.height() ? rect.height():rect.width());
	return minLen;
}

QPointF NodeGraphicsScene::sceneCoorToNormCoor( QPointF point )
{
	qreal minLen = shorterSceneRectSide();
	qreal x = point.x()/(minLen*mRatio)-mOffset.x();
	qreal y = -point.y()/(minLen*mRatio)-mOffset.y();
	return QPointF(x, y);
}
