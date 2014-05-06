#ifndef COMMONNODEGRAPHICSCONFIGDIALOG_H
#define COMMONNODEGRAPHICSCONFIGDIALOG_H

#include <QDialog>

class QGridLayout;

class CommonNodeGraphicsConfigDialog : public QDialog
{
	Q_OBJECT

public:
	CommonNodeGraphicsConfigDialog(QWidget *parent=0);
	~CommonNodeGraphicsConfigDialog();

	CommonNodeGraphicsConfigDialog& setInnerColorList(QList<QColor>);
	CommonNodeGraphicsConfigDialog& setBorderColorList(QList<QColor>);
	CommonNodeGraphicsConfigDialog& setHaveBorderList(QList<bool>);
	CommonNodeGraphicsConfigDialog& setSizeList(QList<qreal>);
	CommonNodeGraphicsConfigDialog& setLabelTextList(QList<QString>);

	QList<QColor> innerColorList() const;
	QList<QColor> borderColorList() const;
	QList<qreal> sizeList() const;
	QList<bool> haveBorderList() const;

	void draw();

public slots:
	void changeInnerColor(QColor,int);
	void changeBorderColor(QColor,int);
	void changeSize(qreal, int);
	void changeHaveBorder(int, int);

private:
	QList<QColor> mInnerColorList;
	QList<QColor> mBorderColorList;
	QList<qreal> mSizeList;
	QList<bool> mHaveBorderList;
	QList<QString> mLabelTextList;

	QGridLayout * mLayout;
	
};

#endif // COMMONNODEGRAPHICSCONFIGDIALOG_H
