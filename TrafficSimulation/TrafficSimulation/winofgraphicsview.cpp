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


WinOfGraphicsView::WinOfGraphicsView(QWidget *parent)
	: QMainWindow(parent)
	, mStatusLabel1(0)
	, mStatusLabel2(0)
{
	ui.setupUi(this);

	initStatusBar();

	loadDataFromDb(); // 在其他操作之前

	//NodeGraphicsScene* scene = new NodeGraphicsScene;
	//RoadLevelGraphicsScene* scene = new RoadLevelGraphicsScene;
	BusNumGraphicsScene* scene = new BusNumGraphicsScene;
	scene->setEdgeDataList(mEdgeDataList).setNodeDataList(mNodeDataList).addItems();
	mView = new GraphicsView(scene);
	connect(scene, SIGNAL(sendMsgToStatus(QString)), this, SLOT(updateStatus(QString)) );
	connect(scene, SIGNAL(clearMsgFromStatus()), this, SLOT(clearTmpMsgFromStatus())  );

	updatePermanentStatus(QStringLiteral("节点数目：")+QString::number(scene->nodeNum()),
		QStringLiteral("路段数目：")+QString::number(scene->edgeNum()) );

	setWindowTitle(QStringLiteral("交通分析成果可视化") );
	showMaximized();
	setCentralWidget(mView);

	 initActions(); // warning: 放在 initToolBar之前
	 initToolBar(); // warning: 放在mView的初始化之后

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
	mPrintAction = new QAction("Print", this);
	mPrintAction->setStatusTip("Print view");
	connect(mPrintAction, SIGNAL(triggered()),mView, SLOT(print()) );

}

void WinOfGraphicsView::initToolBar()
{
	mToolBar = addToolBar("toolbar");
	mToolBar->addAction(mPrintAction);
}

void WinOfGraphicsView::loadDataFromDb()
{
	mNodeDataList = mDbAdapter.loadNormNodes();
	mEdgeDataList = mDbAdapter.loadEdges();
	mBusRouteList = mDbAdapter.loadBusRoutes();
	
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


}




