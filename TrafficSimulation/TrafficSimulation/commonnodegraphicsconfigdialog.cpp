#include "commonnodegraphicsconfigdialog.h"
#include <QGridLayout>
#include <QLabel>
#include "coloredit.h"
#include "spinbox.h"
#include "thickdotwidget.h"
#include "checkbox.h"
#include "thicklinewidget.h"
#include <QPushButton>

CommonNodeGraphicsConfigDialog::CommonNodeGraphicsConfigDialog(QWidget *parent)
	: QDialog(parent)
	, mLayout(0)
{
	setModal(true);
	setWindowTitle(QStringLiteral("ªÊ÷∆ Ù–‘≈‰÷√"));
}

CommonNodeGraphicsConfigDialog::~CommonNodeGraphicsConfigDialog()
{

}

CommonNodeGraphicsConfigDialog& CommonNodeGraphicsConfigDialog::setInnerColorList(QList<QColor> colorList)
{
	mInnerColorList = colorList;
	return *this;
}

CommonNodeGraphicsConfigDialog& CommonNodeGraphicsConfigDialog::setBorderColorList(QList<QColor> colorList)
{
	mBorderColorList = colorList;
	return *this;
}

CommonNodeGraphicsConfigDialog& CommonNodeGraphicsConfigDialog::setHaveBorderList(QList<bool> haveList)
{
	mHaveBorderList = haveList;
	return *this;
}

CommonNodeGraphicsConfigDialog& CommonNodeGraphicsConfigDialog::setSizeList(QList<qreal> sizeList)
{
	mSizeList = sizeList;
	return *this;
}

QList<QColor> CommonNodeGraphicsConfigDialog::innerColorList() const
{
	return mInnerColorList;
}

QList<QColor> CommonNodeGraphicsConfigDialog::borderColorList() const
{
	return mBorderColorList;
}

QList<qreal> CommonNodeGraphicsConfigDialog::sizeList() const
{
	return mSizeList;
}

QList<bool> CommonNodeGraphicsConfigDialog::haveBorderList() const
{
	return mHaveBorderList;
}

void CommonNodeGraphicsConfigDialog::draw()
{
	mLayout = new QGridLayout;
	setLayout(mLayout);
	int rowNum;
	int i=0;
	for(; i<mLabelTextList.size()-1; ++i){
		rowNum = mLayout->rowCount();
		QLabel* label = new QLabel(mLabelTextList.at(i));
		ThickDotWidget* dot = new ThickDotWidget(mSizeList.at(i), mInnerColorList.at(i),
			mBorderColorList.at(i), mHaveBorderList.at(i));
		ColorEdit* colorEdit = new ColorEdit(mInnerColorList.at(i), i);
		connect(colorEdit, SIGNAL(colorChanged(QColor,int)), dot, SLOT(changeInnerColor(QColor)));
		connect(colorEdit, SIGNAL(colorChanged(QColor,int)), this, SLOT(changeInnerColor(QColor,int)));
		ColorEdit* borderColorEdit = new ColorEdit(mBorderColorList.at(i),i);
		connect(borderColorEdit, SIGNAL(colorChanged(QColor,int)), dot, SLOT(changeBorderColor(QColor)));
		connect(borderColorEdit, SIGNAL(colorChanged(QColor,int)), this, SLOT(changeBorderColor(QColor,int)));
		SpinBox* input = new SpinBox;
		input->setId(i);
		input->setValue(mSizeList.at(i));
		connect(input, SIGNAL(valueChanged(double)), dot, SLOT(changeSize(qreal)));
		connect(input, SIGNAL(valueChange(qreal,int)), this, SLOT(changeSize(qreal,int)));
		CheckBox* box = new CheckBox;
		box->setId(i);
		box->setChecked(mHaveBorderList.at(i));
		connect(box, SIGNAL(stateChanged(int)), dot, SLOT(changeHaveBorder(int)));
		connect(box, SIGNAL(stateChange(int, int)), this, SLOT(changeHaveBorder(int, int)));
		mLayout->addWidget(label, rowNum, 0);
		mLayout->addWidget(dot, rowNum, 1);
		mLayout->addWidget(colorEdit, rowNum, 2);
		mLayout->addWidget(borderColorEdit, rowNum, 3);
		mLayout->addWidget(input, rowNum, 4);
		mLayout->addWidget(box, rowNum, 5);
	}
	rowNum = mLayout->rowCount();
	QLabel* label = new QLabel(mLabelTextList.last());
	ThickLineWidget* line = new ThickLineWidget(mSizeList.last(), mInnerColorList.last(),
		mBorderColorList.last(), mHaveBorderList.last());
	ColorEdit* innerColorEdit = new ColorEdit(mInnerColorList.last(), i);
	ColorEdit* borderColorEdit = new ColorEdit(mBorderColorList.last(), i);
	SpinBox* input = new SpinBox;
	input->setId(i);
	input->setValue(mSizeList.last());
	CheckBox* box = new CheckBox;
	box->setId(i);
	box->setChecked(mHaveBorderList.last());
	connect(innerColorEdit, SIGNAL(colorChanged(QColor,int)), line, SLOT(changeInnerColor(QColor)));
	connect(innerColorEdit, SIGNAL(colorChanged(QColor,int)), this, SLOT(changeInnerColor(QColor,int)));
	connect(borderColorEdit, SIGNAL(colorChanged(QColor,int)), line, SLOT(changeBorderColor(QColor)));
	connect(borderColorEdit, SIGNAL(colorChanged(QColor,int)), this, SLOT(changeBorderColor(QColor,int)));
	connect(input, SIGNAL(valueChanged(double)), line, SLOT(changeSize(qreal)));
	connect(input, SIGNAL(valueChange(qreal,int)), this, SLOT(changeSize(qreal,int)));
	connect(box, SIGNAL(stateChanged(int)), line, SLOT(changeHaveBorder(int)));
	connect(box, SIGNAL(stateChange(int, int)), this, SLOT(changeHaveBorder(int, int)));
	mLayout->addWidget(label, rowNum, 0);
	mLayout->addWidget(line, rowNum, 1);
	mLayout->addWidget(innerColorEdit, rowNum, 2);
	mLayout->addWidget(borderColorEdit, rowNum, 3);
	mLayout->addWidget(input, rowNum, 4);
	mLayout->addWidget(box, rowNum, 5);

	QPushButton* okBtn = new QPushButton("OK");
	QPushButton* cancelBtn = new QPushButton("Cancel");
	connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
	rowNum = mLayout->rowCount();
	mLayout->addWidget(okBtn, rowNum, 2);
	mLayout->addWidget(cancelBtn, rowNum, 3);


}

CommonNodeGraphicsConfigDialog& CommonNodeGraphicsConfigDialog::setLabelTextList(QList<QString> textList)
{
	mLabelTextList = textList;
	return *this;
}

void CommonNodeGraphicsConfigDialog::changeInnerColor(QColor color ,int i)
{
	mInnerColorList[i] = color;
}

void CommonNodeGraphicsConfigDialog::changeBorderColor(QColor color,int i)
{
	mBorderColorList[i] = i;
}

void CommonNodeGraphicsConfigDialog::changeSize(qreal s, int i)
{
	mSizeList[i] = s;
}

void CommonNodeGraphicsConfigDialog::changeHaveBorder(int have, int i)
{
	mHaveBorderList[i] = have;
}
