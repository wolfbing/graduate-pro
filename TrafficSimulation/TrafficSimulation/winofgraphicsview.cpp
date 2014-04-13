#include "winofgraphicsview.h"

#include "nodegraphicsscene.h"
#include "roadlevelgraphicsscene.h"
#include "busnumgraphicsscene.h"
#include "graphicsview.h"
#include <QGraphicsView>
#include <QGLWidget>
#include <QPrinter>
#include <QPrintDialog>
#include "BusRoute.h"
#include "structsfordb.h"
#include "junctiontypegraphicsscene.h"
#include "TurnRestrict.h"
#include "turnrestrictgraphicsscene.h"


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
	, mScene(0)
	, mSelectWidget(0)
{
	ui.setupUi(this);

	initStatusBar();

	loadDataFromDb(); // 在其他操作之前

	mView = new GraphicsView;
	setCentralWidget(mView);

	setWindowTitle(QStringLiteral("交通分析成果可视化") );
	showMaximized();
	setCentralWidget(mView);

	initActions(); // warning: 放在 initToolBar之前
	initToolBar(); // warning: 放在mView的初始化之后

	if (!mSelectWidget)
	{
		mSelectWidget = new SelectGraphicsWidget(this);
		connect(mSelectWidget, SIGNAL(selectGraphics(int,int)),this,SLOT(changeScene(int,int)) );
	}
	
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

void WinOfGraphicsView::initActions()
{
	mSelectSceneAction = new QAction("Open", this);
	mSelectSceneAction->setStatusTip("select graphic");
	connect(mSelectSceneAction, SIGNAL(triggered()),this, SLOT(selectGraphics()));
	mPrintAction = new QAction("Print", this);
	mPrintAction->setStatusTip("Print view");
	connect(mPrintAction, SIGNAL(triggered()),mView, SLOT(print()) );
	
}

void WinOfGraphicsView::initToolBar()
{
	mToolBar = addToolBar("toolbar");
	mToolBar->addAction(mSelectSceneAction);
	mToolBar->addAction(mPrintAction);
}

void WinOfGraphicsView::loadDataFromDb()
{
	mNodeDataList = mDbAdapter.loadNormNodes();
	mEdgeDataList = mDbAdapter.loadEdges();
	mBusRouteList = mDbAdapter.loadBusRoutes();
	mTurnRestrictionList = mDbAdapter.loadTurnRestrictions();
	
	{  ///// 对Edge中的Node初始化
		QHash<int,Node*> idNodeHash;
		Node * tmpNode;
		QListIterator<Node*> nodeIte(mNodeDataList);
		while (nodeIte.hasNext())
		{
			tmpNode = nodeIte.next();
			idNodeHash.insert(tmpNode->id(), tmpNode);
		}
		Edge * tmpEdge;
		QListIterator<Edge*> edgeIte(mEdgeDataList);
		int sourceNodeId;
		int destNodeId;
		while (edgeIte.hasNext())
		{
			tmpEdge = edgeIte.next();
			sourceNodeId = tmpEdge->sourceNodeId();
			destNodeId = tmpEdge->destNodeId();
			tmpEdge->setDestNode(idNodeHash.value(destNodeId));
			tmpEdge->setSourceNode(idNodeHash.value(sourceNodeId));
		}
	} //// 对Edge中的Node初始化

	{ ///// 计算每条路段上的公交路线数量
		Edge * tmpEdge;
		QHash<TwoInt, Edge*> nopairEdgeHash;
		QListIterator<Edge*> edgeIte(mEdgeDataList);
		while (edgeIte.hasNext())
		{
			tmpEdge = edgeIte.next();
			TwoInt pk(tmpEdge->sourceNode()->no(), tmpEdge->destNode()->no());
			nopairEdgeHash.insert(pk, tmpEdge);
		}
		QListIterator<BusRoute*> routeIte(mBusRouteList);
		QList<int> stops;
		BusRoute* tmpRoute;
		while (routeIte.hasNext())
		{
			tmpRoute = routeIte.next();
			stops = tmpRoute->stops();
			for(int i=0; i<stops.size()-1; ++i)
			{
				tmpEdge = nopairEdgeHash.value(TwoInt(stops.at(i), stops.at(i+1)));
				if(tmpEdge)
					tmpEdge->addBus();
			};
		}

	} ////// 完成计算每条线路上的公交数量

	{ //// 节点是否是限制转弯的
		QHash<int,Node*> noNodeHash;
		QListIterator<Node*> nodeDataIte(mNodeDataList);
		Node * tmpNode;
		while (nodeDataIte.hasNext())
		{
			tmpNode = nodeDataIte.next();
			noNodeHash.insert(tmpNode->id(), tmpNode);
		}
		QListIterator<TurnRestrict*> turnIte(mTurnRestrictionList);
		TurnRestrict * restr;
		while (turnIte.hasNext())
		{
			restr = turnIte.next();
			tmpNode = noNodeHash.value(restr->currentNodeNo());
			tmpNode->setHaveTurnRestrict(true);
		}

	}

}

void WinOfGraphicsView::changeScene( int index1, int index2 )
{
	switch (index1)
	{
	case 0:
		switch (index2)
		{
		case 0:
			mScene = new RoadLevelGraphicsScene;
			break;
		case 1:
			mScene = new NodeGraphicsScene;
			break;
		case 2:
			mScene = new BusNumGraphicsScene;
		default:
			break;
		}
		break;
	case 1:
		switch (index2)
		{
		case 0:
			mScene = new JunctionTypeGraphicsScene;
			break;
		case 1:
			mScene = new TurnRestrictGraphicsScene;
			break;
		default:
			break;
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
	
	mScene->setEdgeDataList(mEdgeDataList).setNodeDataList(mNodeDataList).addItems();
	connect(mScene, SIGNAL(sendMsgToStatus(QString)), this, SLOT(updateStatus(QString)) );
	connect(mScene, SIGNAL(clearMsgFromStatus()), this, SLOT(clearTmpMsgFromStatus())  );
	updatePermanentStatus(QStringLiteral("节点数目：")+QString::number(mScene->nodeNum()),
		QStringLiteral("路段数目：")+QString::number(mScene->edgeNum()) );
	mView->setScene(mScene);
}

void WinOfGraphicsView::showEvent( QShowEvent * evt )
{
	if (!mSelectWidget)
	{
		mSelectWidget = new SelectGraphicsWidget(this);
		connect(mSelectWidget, SIGNAL(selectGraphics(int,int)),this,SLOT(changeScene(int,int)) );
	}
	if(!mScene)
		mSelectWidget->show();
	QMainWindow::showEvent(evt);
}

void WinOfGraphicsView::selectGraphics()
{
	mSelectWidget->show();
}




