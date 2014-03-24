#include "roadlevelgraphicswidget.h"
#include <QPainter>
#include <QPaintEvent>
#include "legendelement.h"
#include "dotwidget.h"
#include "linewidget.h"
#include "legend.h"

RoadLevelGraphicsWidget::RoadLevelGraphicsWidget(QWidget *parent)
	: GraphicsWidget(parent)
	, mConnList(0)
{
	mConnList = mDbAdapter.loadNormConnWithLevel();
	init(); // 初始化配色线宽等
}

RoadLevelGraphicsWidget::~RoadLevelGraphicsWidget()
{
	if(mConnList)
		delete mConnList;
}



void RoadLevelGraphicsWidget::paintGraphics(QPainter& p, QPaintEvent* event )
{
	QPainterPath path0, path1, path2, path3, path4, path5, path6;
	QListIterator<ConnWithCoorLevel> ite(*mConnList);
	ConnWithCoorLevel conn;
	while (ite.hasNext())
	{
		conn = ite.next();
		QPointF firstPoint = normCoorToScreenCoor(conn.mCoorPair.first);
		QPointF secondPoint = normCoorToScreenCoor(conn.mCoorPair.second);
		switch (conn.mRoadLevel)
		{
		case 0:
			path0.moveTo(firstPoint);
			path0.lineTo(secondPoint);
			break;
		case 1:
			path1.moveTo(firstPoint);
			path1.lineTo(secondPoint);
			break;
		case 2:
			path2.moveTo(firstPoint);
			path2.lineTo(secondPoint);
			break;
		case 3:
			path3.moveTo(firstPoint);
			path3.lineTo(secondPoint);
			break;
		case 4:
			path4.moveTo(firstPoint);
			path4.lineTo(secondPoint);
			break;
		case 5:
			path5.moveTo(firstPoint);
			path5.lineTo(secondPoint);
			break;
		case 6:
			path6.moveTo(firstPoint);
			path6.lineTo(secondPoint);
			break;
		default:
			break;
		}

	}// path整理循环结束

	//城市高架道路 
	QPen pen0(QBrush(mColor0),mWidth0-2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);   
	QPen outPen0(QBrush(mOutColor0),mWidth0, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	// 城市快速干道
	QPen outPen1(QBrush(mOutColor1),mWidth1, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen pen1(QBrush(mColor1),mWidth1-2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin); // 
	// 城市主干道  主干路(同国道、省道)：内线RGB(254，252，193)，外线RGB(221，217，188)
	QPen pen2(QBrush(mColor2),mWidth2-2,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin); 
	QPen outPen2(QBrush(mOutColor2),mWidth2,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	// 城市次干道
	QPen pen3(QBrush(mColor3),mWidth3-2,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin); 
	QPen outPen3(QBrush(mOutColor3),mWidth3,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	// 城市支路
	QPen pen4(QBrush(mColor4),mWidth4,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin); 
	// 郊区公路
	QPen pen5(QBrush(mColor5),mWidth5,Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	// 高速公路  高速公路：内线RGB(253，206，102)，外线RGB(203，168，87)；
	QPen pen6(QBrush(mColor6), mWidth6-2, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	QPen outPen6(QBrush(mOutColor6), mWidth6, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
	// ---- 画图 ----
	// 郊区公路
	p.setPen(pen5); p.drawPath(path5);
	// 城市支路
	p.setPen(pen4); p.drawPath(path4);
	// 次干道
	p.setPen(outPen3); p.drawPath(path3); p.setPen(pen3); p.drawPath(path3);
	// 主干道
	p.setPen(outPen2); p.drawPath(path2); p.setPen(pen2); p.drawPath(path2);
	//快速干道
	p.setPen(outPen1); p.drawPath(path1); p.setPen(pen1); p.drawPath(path1);
	// 高速公路
	p.setPen(outPen6); p.drawPath(path6); p.setPen(pen6); p.drawPath(path6);
	// 高架
	p.setPen(pen0); p.drawPath(path0);


}

void RoadLevelGraphicsWidget::createLegend()
{
	if (mLegend)
	{
		mLegend->show();
		return;
	}
	QList<LegendElement> li;
	LegendElement line0(QStringLiteral("城市高架道路"),LegendElement::THICK_LINE,mWidth0,mColor0,mOutColor0);
	LegendElement line1(QStringLiteral("城市快速干道"),LegendElement::THICK_LINE,mWidth1,mColor1,mOutColor1);
	LegendElement line2(QStringLiteral("城市主干道"),LegendElement::THICK_LINE,mWidth2,mColor2,mOutColor2);
	LegendElement line3(QStringLiteral("城市次干道"),LegendElement::THICK_LINE,mWidth3,mColor3,mOutColor3);
	LegendElement line4(QStringLiteral("城市支路"),LegendElement::LINE,mWidth4,mColor4);
	LegendElement line5(QStringLiteral("郊区公路"),LegendElement::LINE,mWidth5,mColor5);
	LegendElement line6(QStringLiteral("高速公路"),LegendElement::THICK_LINE,mWidth6,mColor6,mOutColor6);
	li.append(line0);
	li.append(line1);
	li.append(line2);
	li.append(line3);
	li.append(line4);
	li.append(line5);
	li.append(line6);
	mLegend = new Legend(li, this);
	mLegend->show();

}

void RoadLevelGraphicsWidget::init()
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


