#include "nodegraphicswidget.h"
#include <QPainter>
#include <QPaintEvent>
#include "thickdotwidget.h"

NodeGraphicsWidget::NodeGraphicsWidget(QWidget *parent)
	: GraphicsWidget(parent)
	, mDbAdapter()
	, mConnList(0)
	, mNodes(0)
{
	mConnList = mDbAdapter.loadNormConns();
	extractNodes(); // 初始化mNodes
	init();
}

NodeGraphicsWidget::~NodeGraphicsWidget()
{
	if(mNodes)
		delete mNodes;
	if(mConnList)
		delete mConnList;

}

void NodeGraphicsWidget::paintGraphics(QPainter& p, QPaintEvent * event)
{
	QRect rect= event->rect();
	int w = rect.width();
	int h = rect.height();
	QPoint center = rect.center();
	int minL = w>h ? h : w;

	// 画线
	p.save();
	QPen linePen(mOutLineColor);
	linePen.setWidthF(mLineWidth);
	p.setPen(linePen);
	QPen innerLinePen(mLineColor);
	innerLinePen.setWidthF(mLineWidth - 2);
	QListIterator<QPair<Node,Node> > ite(*mConnList);
	QLine line;
	while (ite.hasNext())
	{
		QPair<Node,Node> conn = ite.next();
		QPointF firstPoint = normCoorToScreenCoor(conn.first.mCoor);
		QPointF secondPoint = normCoorToScreenCoor(conn.second.mCoor);
		line.setLine(firstPoint.x(),firstPoint.y(),secondPoint.x(),secondPoint.y());
		p.drawLine(line);
		p.save();
		p.setPen(innerLinePen);
		p.drawLine(line);
		p.restore();
	}
	p.restore();
	// 画节点
	p.save();
	QPen nodePen(mNodePenColor);
	QBrush nodeBrush(mNodeBrushColor);
	p.setPen(nodePen);
	p.setBrush(nodeBrush);
	QHashIterator<Node,qreal> iteNode(*mNodes);
	QPointF point;
	while (iteNode.hasNext())
	{
		iteNode.next();
		point = normCoorToScreenCoor(iteNode.key().mCoor);
		p.drawEllipse(point.x()-mNodeRadius,
			point.y()-mNodeRadius,2*mNodeRadius,2*mNodeRadius); 
	}
	p.restore();
	// 写节点标号
	p.save();
	iteNode.toFront();
	while (iteNode.hasNext())
	{
		iteNode.next();
		point = normCoorToScreenCoor(iteNode.key().mCoor) ;
		if(iteNode.value()*minL*getRatio() > 25){ // 阈值的设置是尝试着设置的
			p.drawText(QPointF(point.x()+5,point.y()),
				QString::number(iteNode.key().mNo)); 
		}
		
	}
	p.restore();

}


void NodeGraphicsWidget::extractNodes()
{
	QListIterator<QPair<Node,Node> > ite(*mConnList);
	QPair<Node,Node> conn;
	if(!mNodes)
		mNodes = new QHash<Node,qreal>;
	while (ite.hasNext())
	{
		conn = ite.next();
		qreal len = length(conn);
		if(!mNodes->contains(conn.first))
			mNodes->insert(conn.first,len);
		else{
			qreal l = mNodes->value(conn.first);
			if(len<l)
				mNodes->insert(conn.first,len);
		}
		if(!mNodes->contains(conn.second))
			mNodes->insert(conn.second,len);
		else
		{
			qreal l = mNodes->value(conn.second);
			if(len<l)
				mNodes->insert(conn.second,len);
		}

	}

}

void NodeGraphicsWidget::createLegend()
{
	if(!mLegend){
		LegendElement node(QStringLiteral("交通节点"),LegendElement::THICK_DOT,
			mNodeRadius,mNodeBrushColor,mNodePenColor);
		LegendElement tLine(QStringLiteral("道路"), LegendElement::THICK_LINE,
			mLineWidth, mLineColor, mOutLineColor);
		QList<LegendElement> li;
		li.append(node);
		li.append(tLine);
		mLegend = new Legend(li,this);
	}
	mLegend->show();

}

void NodeGraphicsWidget::init()
{
	mNodePenColor = QColor(38,0,0) ;
	mNodeBrushColor = QColor(178,73,77);
	mNodeRadius = 4.0;
	mOutLineColor = QColor(203,168,87);
	mLineColor = QColor(253,206,102);
	mLineWidth = 4.0;
}
