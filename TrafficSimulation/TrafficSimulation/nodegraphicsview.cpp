#include "nodegraphicsview.h"
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>

NodeGraphicsView::NodeGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
	, mIsPressed(false)
{
}

NodeGraphicsView::NodeGraphicsView( NodeGraphicsScene* scene, QWidget* parent/*=0*/ )
	: QGraphicsView(scene, parent)
{
	setRenderHint(QPainter::Antialiasing);
	connect(this, SIGNAL(sizeChange(int, int)), scene, SLOT(changeSceneRect(int, int)));
	connect(this, SIGNAL(zoom(int, QPointF)), scene, SLOT(zoom(int, QPointF)));
	connect(this, SIGNAL(move(QPointF)), scene, SLOT(move(QPointF)));
}

NodeGraphicsView::~NodeGraphicsView()
{

}

void NodeGraphicsView::resizeEvent( QResizeEvent *event )
{
	QSize size = event->size();
	emit sizeChange(size.width(), size.height());
}

void NodeGraphicsView::wheelEvent( QWheelEvent *event )
{
	QPoint numDegrees = event->angleDelta()/8;
	QPoint numSteps = numDegrees/15;
	QPoint hoverPos = event->pos();
	QPointF scenePos = mapToScene(hoverPos);
	emit zoom(numSteps.y(), scenePos);
}

void NodeGraphicsView::mousePressEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton){
		mIsPressed = true;
		mPressPos = event->pos();
	}
		
}

void NodeGraphicsView::mouseReleaseEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton)
		mIsPressed = false;
}

void NodeGraphicsView::mouseMoveEvent( QMouseEvent *event )
{
	if (mIsPressed)
	{
		QPoint currentPos = event->pos();
		QPointF pos1 = mapToScene(mPressPos);
		QPointF pos2 = mapToScene(currentPos);
		mPressPos = currentPos;
		emit move(pos2 - pos1);
	}
}
