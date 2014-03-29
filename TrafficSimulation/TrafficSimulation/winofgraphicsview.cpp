#include "winofgraphicsview.h"

#include "nodegraphicsscene.h"
#include "nodegraphicsview.h"
#include <QGraphicsView>
#include <QGLWidget>


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	NodeGraphicsScene* scene = new NodeGraphicsScene;
	NodeGraphicsView* view = new NodeGraphicsView(scene);
	
	setCentralWidget(view);

}

WinOfGraphicsView::~WinOfGraphicsView()
{

}


