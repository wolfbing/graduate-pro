#include "trafficsimulation.h"
#include "nodegraphicsscene.h"
#include <QGraphicsView>

TrafficSimulation::TrafficSimulation(QWidget *parent)
	: QMainWindow(parent)
	, mSelectGraphicsDialog(0)
	, mNoGraphics(true)
	, mCurrentComIndex(-1)
	, mCurrentListIndex(-1)
	, mPrintAction(0)
{
	ui.setupUi(this);
	
	// 初始化工作
	initActions();
	initToolBar();

	showMaximized();

}

TrafficSimulation::~TrafficSimulation()
{
	
}

void TrafficSimulation::initActions()
{
	mSelectGraphicsAction = new QAction("select graphics", this);
	mPrintAction = new QAction("print", this);

	connect(mSelectGraphicsAction,SIGNAL(triggered()),this, SLOT(showSelectGraphicsDialog()));

}

void TrafficSimulation::initToolBar()
{
	mToolBar = addToolBar("tool");
	mToolBar->addAction(mSelectGraphicsAction);
	mToolBar->addAction(mPrintAction);
}

void TrafficSimulation::showSelectGraphicsDialog()
{
	if(!mSelectGraphicsDialog)
	{
		mSelectGraphicsDialog = new SelectGraphicsWidget(this);
		// 绑定紧跟着地址的申请，避免绑定到无用的指针
		connect(mSelectGraphicsDialog,SIGNAL(selectedGraphics(int,int)),
			this,SLOT(changeGraphics(int,int)));
	}
	mSelectGraphicsDialog->show();
}

void TrafficSimulation::changeGraphics( int comIndex,int listIndex )
{
	if(comIndex == mCurrentComIndex && listIndex == mCurrentListIndex)
		return ;
	mCurrentComIndex = comIndex;
	mCurrentListIndex = listIndex;
	/*switch (comIndex)
	{
	case 0:
		{
			switch (listIndex)
			{
			case 0:
				{
					mRoadLevelWidget = new RoadLevelGraphicsWidget(this);
					this->setCentralWidget(mRoadLevelWidget);
					connect(mPrintAction,SIGNAL(triggered()), mRoadLevelWidget,SLOT(printGraphics()));
					break;
				}
			case 1:
				{
					mNodeWidget = new NodeGraphicsWidget(this);
					this->setCentralWidget(mNodeWidget);
					connect(mPrintAction,SIGNAL(triggered()), mNodeWidget,SLOT(printGraphics()));
					break;
				}
			case 2:
				{
					mBusNumWidget = new BusNumGraphicsWidget(this);
					this->setCentralWidget(mBusNumWidget);
					connect(mPrintAction,SIGNAL(triggered()), mBusNumWidget,SLOT(printGraphics()));
					break;
				}
			default:
				break;
			}

		}
	default:
		break;
	}*/
	mNoGraphics = false;
	update();
}

void TrafficSimulation::paintEvent( QPaintEvent * e )
{
	QMainWindow::paintEvent(e);
	if(mNoGraphics)
		showSelectGraphicsDialog();
}




