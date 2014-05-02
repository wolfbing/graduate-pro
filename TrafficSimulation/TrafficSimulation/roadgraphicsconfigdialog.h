#ifndef ROADGRAPHICSCONFIGDIALOG_H
#define ROADGRAPHICSCONFIGDIALOG_H

#include <QDialog>


class RoadGraphicsConfigDialog : public QDialog
{
	Q_OBJECT

public:
	RoadGraphicsConfigDialog(QWidget *parent = 0);
	~RoadGraphicsConfigDialog();
	//// get
	QList<QColor> colorList() const;
	QList<qreal> widthList() const;
	///// set
	RoadGraphicsConfigDialog& setColorList(QList<QColor>);
	RoadGraphicsConfigDialog& setWidthList(QList<qreal>);
	RoadGraphicsConfigDialog& setLabelTextList(QList<QString>);

	void draw();

public slots:
	void changeColor(QColor, int);
	void changeWidth(qreal, int);

private:
	QList<QString> mLabelTextList;
	QList<QColor> mColorList;
	QList<qreal> mWidthList;
	
};

#endif // ROADGRAPHICSCONFIGDIALOG_H
