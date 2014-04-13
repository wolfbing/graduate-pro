#include "graphicsscene.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "node.h"

GraphicsScene::GraphicsScene(QObject *parent)
	: QGraphicsScene(parent)
	, mRatio(0.9)
	, mOffset(QPointF(0,0))
	, mBackColor(QColor(242,239,232))
	, mLeftBtnPressed(false)
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
	doSomething();
}

void GraphicsScene::changeSceneRect( int w, int h )
{
	setSceneRect(-w/2.0, -h/2.0, w, h);
	updateItems();
	doSomething();
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

void GraphicsScene::drawBackground( QPainter *painter, const QRectF &rect )
{
	painter->fillRect(rect, mBackColor);
}


void GraphicsScene::mouseMoveEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsScene::mouseMoveEvent(event);
	if(event->isAccepted())
		return ;

	if (event->buttons() & Qt::LeftButton)
	{
		QPointF p1 = event->lastScenePos();
		QPointF p2 = event->scenePos();
		QPointF delta = p2 - p1;
		move(delta);
		event->accept();
	}
	
}

void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsScene::mousePressEvent(event);
	if(event->isAccepted())
		return ;
	event->accept();
}

void GraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent *event )
{
	QGraphicsScene::mouseReleaseEvent(event);
	if(event->isAccepted())
		return ;
	event->accept();
}

GraphicsScene & GraphicsScene::setNodeDataList( QList<Node*> list )
{
	mNodeDataList = list;
	return *this;
}

GraphicsScene & GraphicsScene::setEdgeDataList( QList<Edge*> list )
{
	mEdgeDataList = list;
	return *this;
}

int GraphicsScene::edgeNum() const
{
	return mEdgeDataList.size();
}

int GraphicsScene::nodeNum() const
{
	return mNodeDataList.size();
}

void GraphicsScene::updateItems()
{
	QListIterator<Node*> nodeDataIte(mNodeDataList);
	Node * tmpNodeData;
	while (nodeDataIte.hasNext())
	{
		tmpNodeData = nodeDataIte.next();
		tmpNodeData->setSceneCoor(normCoorToSceneCoor(tmpNodeData->coor()));
	}
}




