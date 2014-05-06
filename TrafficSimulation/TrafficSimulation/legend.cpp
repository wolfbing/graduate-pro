#include "legend.h"
#include "linewidget.h"
#include "dotwidget.h"
#include "thicklinewidget.h"
#include "thickdotwidget.h"

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>
#include <QtWidgets\qgridlayout.h>
#include <QMoveEvent>
#include <QPalette>
#include <QDebug>


Legend::Legend(QList<LegendElement> elements, QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
	,mElements(elements)
	, mFirstShow(true)
	, mLayout(0)
{
    this->setWindowTitle(tr("legend"));
    this->setWindowOpacity(0.75);

    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::MinimumExpanding);
	this->setMinimumWidth(200);
	this->setMinimumHeight(100);

	draw();
}

Legend *Legend::setElements(QList<LegendElement> elelist)
{
    mElements = elelist;
    return this;
}

void Legend::draw(){
	if(!mLayout)
		mLayout = new QGridLayout;
	this->setLayout(mLayout);
	for(int i=0; i<mElements.size(); ++i){
		LegendElement element = mElements.at(i);
		int rowNum = mLayout->rowCount();
		if(element.type() == LegendElement::DOT ){
			QLabel* label = new QLabel(element.name());
			DotWidget* dotWidget = new DotWidget;
			dotWidget->setColor(element.color1());
			dotWidget->setRadius(element.size());
			mLayout->addWidget(label, rowNum, 0);
			mLayout->addWidget(dotWidget, rowNum, 1);
			mWidgetList << dotWidget << label;
			
		}
		if(element.type() == LegendElement::LINE){
			QLabel* label = new QLabel(element.name());
			LineWidget* lineWidget = new LineWidget;
			lineWidget->setColor(element.color1());
			lineWidget->setWidth(element.size());
			mLayout->addWidget(label, rowNum, 0);
			mLayout->addWidget(lineWidget,rowNum,1);
			mWidgetList << label << lineWidget;
		}
		if (element.type() == LegendElement::THICK_LINE)
		{
			QLabel* label = new QLabel(element.name());
			ThickLineWidget* tLineWidget = new ThickLineWidget(
				element.size(), element.color1(),element.color2());
			mLayout->addWidget(label,rowNum, 0);
			mLayout->addWidget(tLineWidget, rowNum,1);
			mWidgetList << label << tLineWidget;
		}
		if (element.type() == LegendElement::THICK_DOT)
		{
			QLabel* label = new QLabel(element.name());
			ThickDotWidget* tDotWidget = new ThickDotWidget(
				element.size(), element.color1(),element.color2());
			mLayout->addWidget(label,rowNum,0);
			mLayout->addWidget(tDotWidget,rowNum,1);
			mWidgetList << label << tDotWidget;
		}
	}
	update();
	
}


void Legend::paintEvent( QPaintEvent * event )
{
	QDialog::paintEvent(event);

}

void Legend::updateAttr(QList<QColor> colorList, QList<qreal> widthList)
{
	for (int i=0; i<mElements.size(); ++i)
	{
		mElements[i].setElementColor1(colorList[i]);
		mElements[i].setElementSize(widthList[i]);
	}
	for (int i=0; i<mWidgetList.size(); ++i)
	{
		mLayout->removeWidget(mWidgetList[i]);
	}
	while (mWidgetList.size()>0)
	{
		delete mWidgetList.takeLast();
	}
	draw();
}

void Legend::updateAttr(QList<QColor> colorList1, QList<QColor> colorList2, QList<qreal> sizeList)
{
	for (int i=0; i<mElements.size(); ++i)
	{
		mElements[i].setElementColor1(colorList1[i]);
		mElements[i].setElementColor2(colorList2[i]);
		mElements[i].setElementSize(sizeList[i]);
	}
	for (int i=0; i<mWidgetList.size(); ++i)
	{
		mLayout->removeWidget(mWidgetList[i]);
	}
	while (mWidgetList.size()>0)
	{
		delete mWidgetList.takeLast();
	}
	draw();
}

QList<LegendElement> Legend::elements() const
{
	return mElements;
}



