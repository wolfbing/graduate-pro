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


Legend::Legend(QList<LegendElement> elements, QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint)
	,mElements(elements)
	, mFirstShow(true)
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
	QGridLayout* layout = new QGridLayout;
	this->setLayout(layout);
	for(int i=0; i<mElements.size(); ++i){
		LegendElement element = mElements.at(i);
		int rowNum = layout->rowCount();
		if(element.type() == LegendElement::DOT ){
			QLabel* label = new QLabel(element.name());
			DotWidget* dotWidget = new DotWidget;
			dotWidget->setColor(element.color1());
			dotWidget->setRadius(element.size());
			layout->addWidget(label, rowNum, 0);
			layout->addWidget(dotWidget, rowNum, 1);
			
		}
		if(element.type() == LegendElement::LINE){
			QLabel* label = new QLabel(element.name());
			LineWidget* lineWidget = new LineWidget;
			lineWidget->setColor(element.color1());
			lineWidget->setWidth(element.size());
			layout->addWidget(label, rowNum, 0);
			layout->addWidget(lineWidget,rowNum,1);
		}
		if (element.type() == LegendElement::THICK_LINE)
		{
			QLabel* label = new QLabel(element.name());
			ThickLineWidget* tLineWidget = new ThickLineWidget(
				element.size(), element.color1(),element.color2());
			layout->addWidget(label,rowNum, 0);
			layout->addWidget(tLineWidget, rowNum,1);
		}
		if (element.type() == LegendElement::THICK_DOT)
		{
			QLabel* label = new QLabel(element.name());
			ThickDotWidget* tDotWidget = new ThickDotWidget(
				element.size(), element.color1(),element.color2());
			layout->addWidget(label,rowNum,0);
			layout->addWidget(tDotWidget,rowNum,1);
		}
	}
	
}


void Legend::paintEvent( QPaintEvent * event )
{
	QDialog::paintEvent(event);

}



