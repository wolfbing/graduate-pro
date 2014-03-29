#include "winofgraphicsview.h"

#include "nodegraphicsscene.h"
#include "graphicsview.h"
#include <QGraphicsView>
#include <QGLWidget>


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
{
	ui.setupUi(this);

	initStatusBar();

	NodeGraphicsScene* scene = new NodeGraphicsScene;
	GraphicsView* view = new GraphicsView(scene);
	connect(scene, SIGNAL(sendMsgToStatus(QString)), this, SLOT(updateStatus(QString)) );
	connect(scene, SIGNAL(clearMsgFromStatus()), this, SLOT(clearTmpMsgFromStatus())  );

	updatePermanentStatus(QStringLiteral("节点数目：")+QString::number(scene->nodeNum()),
		QStringLiteral("路段数目：")+QString::number(scene->edgeNum()) );

	setWindowTitle(QStringLiteral("交通分析成果可视化") );
	showMaximized();
	setCentralWidget(view);

	 

}

WinOfGraphicsView::~WinOfGraphicsView()
{

}

void WinOfGraphicsView::updateStatus( QString msg )
{
	statusBar()->showMessage(msg);

}

void WinOfGraphicsView::clearTmpMsgFromStatus()
{
	statusBar()->clearMessage();
}

void WinOfGraphicsView::initStatusBar()
{
	mStatusLabel1 = new QLabel;
	mStatusLabel2 = new QLabel;
	statusBar()->addPermanentWidget(mStatusLabel1);
	statusBar()->addPermanentWidget(mStatusLabel2);
}

void WinOfGraphicsView::updatePermanentStatus(QString str1, QString str2)
{
	mStatusLabel1->setText(str1+"    ");
	mStatusLabel2->setText(str2+"    ");
}


