#include "roadgraphicsconfigdialog.h"
#include <QGridLayout>
#include <QLabel>
#include "linewidget.h"
#include "coloredit.h"
#include <QDoubleSpinBox>
#include <QPushButton>
#include "spinbox.h"

RoadGraphicsConfigDialog::RoadGraphicsConfigDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowTitle(QStringLiteral("ªÊ÷∆ Ù–‘≈‰÷√"));
	//draw();
}

RoadGraphicsConfigDialog::~RoadGraphicsConfigDialog()
{

}

QList<QColor> RoadGraphicsConfigDialog::colorList() const
{
	return mColorList;
}

QList<qreal> RoadGraphicsConfigDialog::widthList() const
{
	return mWidthList;
}

void RoadGraphicsConfigDialog::draw()
{
	QGridLayout* layout = new QGridLayout;
	setLayout(layout);
	int rowNum = layout->rowCount();
	QLabel* headLabel1 = new QLabel("item");
	QLabel* headLabel2 = new QLabel("line");
	QLabel* headLabel3 = new QLabel("color");
	QLabel* headLabel4 = new QLabel("width");
	layout->addWidget(headLabel1, rowNum, 0);
	layout->addWidget(headLabel2, rowNum, 1);
	layout->addWidget(headLabel3, rowNum, 2);
	layout->addWidget(headLabel4, rowNum, 3);
	for (int i=0; i<mLabelTextList.size(); ++i)
	{
		rowNum = layout->rowCount();
		QLabel* textLabel = new QLabel(mLabelTextList.at(i));
		LineWidget* line = new LineWidget;
		line->setColor(mColorList.at(i));
		line->setWidth(mWidthList.at(i));
		ColorEdit* colorEdit = new ColorEdit(mColorList.at(i),i);
		connect(colorEdit, SIGNAL(colorChanged(QColor,int)), line, SLOT(changeColor(QColor)));
		connect(colorEdit, SIGNAL(colorChanged(QColor,int)), this, SLOT(changeColor(QColor, int)));
		//QDoubleSpinBox* input = new QDoubleSpinBox;
		SpinBox* input = new SpinBox;
		input->setValue(mWidthList.at(i));
		input->setId(i);
		connect(input, SIGNAL(valueChanged(double)), line, SLOT(changeWidth(qreal)));
		connect(input, SIGNAL(valueChange(qreal, int)), this, SLOT(changeWidth(qreal, int)));
		layout->addWidget(textLabel,rowNum,0);
		layout->addWidget(line, rowNum, 1);
		layout->addWidget(colorEdit, rowNum, 2);
		layout->addWidget(input, rowNum, 3);
		
	}
	QPushButton* okBtn = new QPushButton("OK");
	QPushButton* cancelBtn = new QPushButton("Cancel");
	connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
	rowNum = layout->rowCount();
	layout->addWidget(okBtn, rowNum, 2);
	layout->addWidget(cancelBtn, rowNum, 3);

}

RoadGraphicsConfigDialog& RoadGraphicsConfigDialog::setColorList(QList<QColor> list)
{
	mColorList = list;
	return *this;
}

RoadGraphicsConfigDialog& RoadGraphicsConfigDialog::setWidthList(QList<qreal> list)
{
	mWidthList = list;
	return *this;
}

RoadGraphicsConfigDialog& RoadGraphicsConfigDialog::setLabelTextList(QList<QString> list)
{
	mLabelTextList = list;
	return *this;
}

void RoadGraphicsConfigDialog::changeColor(QColor color, int id)
{
	mColorList[id] = color;
}

void RoadGraphicsConfigDialog::changeWidth(qreal width, int i)
{
	mWidthList[i] = width;
}
