#include "roadlevelgraphicsscene.h"
#include "Edge.h"
#include "graphicsedgeitem.h"
#include "node.h"

RoadLevelGraphicsScene::RoadLevelGraphicsScene(QObject *parent)
	: GraphicsScene(parent)
{
	init(); // 在其他操作前进行
	QList<Edge>* edgeDataList = mDbAdapter.loadEdgeWithCoorLevel();
	Edge tmpEdge;
	Node * tmpNode;
	GraphicsEdgeItem* item;
	QListIterator<Edge> ite(*edgeDataList);
	while (ite.hasNext())
	{
		tmpEdge = ite.next();
		item = new GraphicsEdgeItem;
		item->setEdgeData(new Edge(tmpEdge));
		item->setWidth(4.0).setBorderColor(Qt::red).setInnerColor(Qt::blue);
		switch (tmpEdge.roadLevel())
		{
		case 0:
			item->setWidth(mWidth0).setInnerColor(mColor0).setBorderColor(mOutColor0).setZValue(6);
			break;
		case 1:
			item->setWidth(mWidth1).setInnerColor(mColor1).setBorderColor(mOutColor1).setZValue(4);
			break;
		case 2:
			item->setWidth(mWidth2).setInnerColor(mColor2).setBorderColor(mOutColor3).setZValue(3);
			break;
		case 3:
			item->setWidth(mWidth3).setInnerColor(mColor3).setBorderColor(mOutColor3).setZValue(2);
			break;
		case 4:
			item->setWidth(mWidth4).setInnerColor(mColor4).setHaveBorder(false).setZValue(1);
			break;
		case 5:
			item->setWidth(mWidth5).setInnerColor(mColor5).setHaveBorder(false).setZValue(0);
			break;
		case 6:
			item->setWidth(mWidth6).setInnerColor(mColor6).setBorderColor(mOutColor6).setZValue(5);
			break;

		default:
			break;
		}
		mEdgeList << item;
		addItem(item);
		connect(item, SIGNAL(sendTmpInfoToStatus(QString)), this, SIGNAL(sendMsgToStatus(QString)) );
		connect(item, SIGNAL(clearTmpInfoFromStatus()), this, SIGNAL(clearMsgFromStatus()) );
		tmpNode = tmpEdge.sourceNode();
		if(!mNodeList.contains(tmpNode))
			mNodeList << tmpNode;
		tmpNode = tmpEdge.destNode();
		if(!mNodeList.contains(tmpNode))
			mNodeList << tmpNode;

	}
	
	setItemIndexMethod(QGraphicsScene::NoIndex);

}

RoadLevelGraphicsScene::~RoadLevelGraphicsScene()
{

}

void RoadLevelGraphicsScene::updateItems()
{
	QListIterator<Node*> ite(mNodeList);
	Node * tmpNode;
	QPointF point;
	while (ite.hasNext())
	{
		tmpNode = ite.next();
		point = normCoorToSceneCoor(tmpNode->coor() );
		tmpNode->setSceneCoor(point);
	}
	QListIterator<GraphicsEdgeItem*> edgeIte(mEdgeList);
	GraphicsEdgeItem* tmpEdge;
	QPointF source, dest;
	while (edgeIte.hasNext())
	{
		tmpEdge = edgeIte.next();
		tmpEdge->advance();
	}
}

void RoadLevelGraphicsScene::init()
{
	mColor0 = QColor(205,168,232); mOutColor0 = QColor(147,102,128);
	mColor1 = QColor(249,126,128); mOutColor1 = QColor(186,98,96);
	mColor2 = QColor(255,225,104); mOutColor2 = QColor(231,195,96);
	mColor3 = QColor(254,252,193); mOutColor3 = QColor(221,217,188);
	mColor4 = QColor(151,189,253);
	mColor5 = QColor(139,182,105);
	mColor6 = QColor(250,158,37); mOutColor6 = QColor(231,160,37);

	mWidth0 = 7.0; 
	mWidth1 = 6.0; 
	mWidth2 = 6.0; 
	mWidth3 = 5.0; 
	mWidth4 = 2.0; 
	mWidth5 = 2.0; 
	mWidth6 = 9.0; 
}









