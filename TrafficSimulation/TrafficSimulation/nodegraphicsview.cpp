#include "nodegraphicsview.h"
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGLWidget>


NodeGraphicsView::NodeGraphicsView( NodeGraphicsScene* scene, QWidget* parent/*=0*/ )
	: QGraphicsView(scene, parent)
{
	init(scene);
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

void NodeGraphicsView::init(NodeGraphicsScene* scene)
{
	mIsPressed = false;
	setRenderHint(QPainter::Antialiasing, false);
	connect(this, SIGNAL(sizeChange(int, int)), scene, SLOT(changeSceneRect(int, int)));
	connect(this, SIGNAL(zoom(int, QPointF)), scene, SLOT(zoom(int, QPointF)));
	connect(this, SIGNAL(move(QPointF)), scene, SLOT(move(QPointF)));
	setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	setCursor(Qt::CrossCursor);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setCacheMode(CacheBackground);
	setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

}


void NodeGraphicsView::mousePressEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton){
		mIsPressed = true;
		mPressScenePos = mapToScene(event->pos());
	}
		
}

void NodeGraphicsView::mouseReleaseEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton)
	{
		mIsPressed = false;
	}
}

void NodeGraphicsView::mouseMoveEvent( QMouseEvent *event )
{
	if (mIsPressed)
	{
		QPointF currentPos = mapToScene(event->pos());
		QPointF delta = currentPos - mPressScenePos;
		mPressScenePos = currentPos;
		emit move(delta);
	}
}
