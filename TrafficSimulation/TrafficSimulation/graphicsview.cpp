#include "graphicsview.h"
#include <QResizeEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QGLWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>


GraphicsView::GraphicsView( GraphicsScene* scene, QWidget* parent/*=0*/ )
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

void GraphicsView::init(GraphicsScene* scene)
{
	mIsPressed = false;
	setRenderHint(QPainter::Antialiasing, false);
	connect(this, SIGNAL(sizeChange(int, int)), scene, SLOT(changeSceneRect(int, int)));
	connect(this, SIGNAL(zoom(int, QPointF)), scene, SLOT(zoom(int, QPointF)));
	connect(this, SIGNAL(move(QPointF)), scene, SLOT(move(QPointF)));
	//setOptimizationFlag(QGraphicsView::DontSavePainterState);
	setViewportUpdateMode(FullViewportUpdate);
	setCursor(Qt::OpenHandCursor);
	setDragMode(QGraphicsView::ScrollHandDrag);
	setCacheMode(CacheBackground);
	setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));

}

void GraphicsView::print()
{
	QPrinter printer;
	if (QPrintDialog(&printer).exec() == QDialog::Accepted) {
		// printer自带的filedialog不能用, 原因未知, 所以手动加了一个
		QString filename = QFileDialog::getSaveFileName(this,"filename",QString(),QString("pdf Files (*.pdf)"));
		printer.setOutputFileName(filename);
		QPainter painter(&printer);
		painter.setRenderHint(QPainter::Antialiasing);
		//开始打印
		render(&painter);
	}
	
}
