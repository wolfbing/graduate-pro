#include "graphicsview.h"
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGLWidget>


GraphicsView::GraphicsView( NodeGraphicsScene* scene, QWidget* parent/*=0*/ )
	: QGraphicsView(scene, parent)
{
	init(scene);
}

GraphicsView::~GraphicsView()
{

}

void GraphicsView::resizeEvent( QResizeEvent *event )
{
	QSize size = event->size();
	emit sizeChange(size.width(), size.height());
}

void GraphicsView::wheelEvent( QWheelEvent *event )
{
	QPoint numDegrees = event->angleDelta()/8;
	QPoint numSteps = numDegrees/15;
	QPoint hoverPos = event->pos();
	QPointF scenePos = mapToScene(hoverPos);
	emit zoom(numSteps.y(), scenePos);
}

void GraphicsView::init(NodeGraphicsScene* scene)
{
	mIsPressed = false;
	setRenderHint(QPainter::Antialiasing, false);
	connect(this, SIGNAL(sizeChange(int, int)), scene, SLOT(changeSceneRect(int, int)));
	connect(this, SIGNAL(zoom(int, QPointF)), scene, SLOT(zoom(int, QPointF)));
	connect(this, SIGNAL(move(QPointF)), scene, SLOT(move(QPointF)));
	setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	setCursor(Qt::OpenHandCursor);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setCacheMode(CacheBackground);
	setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

}


void GraphicsView::mousePressEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton){
		mIsPressed = true;
		mPressScenePos = mapToScene(event->pos());
		//setCursor(Qt::ClosedHandCursor);
	}
	QGraphicsView::mousePressEvent(event);
}

void GraphicsView::mouseReleaseEvent( QMouseEvent *event )
{
	if(event->button() == Qt::LeftButton)
	{
		mIsPressed = false;
		//unsetCursor();
	}
	QGraphicsView::mouseReleaseEvent(event);
}

void GraphicsView::mouseMoveEvent( QMouseEvent *event )
{
	if (mIsPressed)
	{
		QPointF currentPos = mapToScene(event->pos());
		QPointF delta = currentPos - mPressScenePos;
		mPressScenePos = currentPos;
		emit move(delta);
	}
	QGraphicsView::mouseMoveEvent(event);
}
