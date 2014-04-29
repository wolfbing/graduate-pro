#ifndef LEGEND_H
#define LEGEND_H

#include <QWidget>
#include <QDialog>

#include <QSize>
#include <QList>

#include "legendelement.h"

/*
* 输入图例内容的name type color等信息, Legend类会根据相应的类型进行绘制
*/
class Legend : public QDialog
{
    Q_OBJECT
public:
    explicit Legend(QList<LegendElement> elements, QWidget *parent=0);
    Legend* setElements(QList<LegendElement> elelist);
	void draw();

signals:
	void posChange(QString);

public slots:

protected:
	void paintEvent(QPaintEvent *);

private:

    QList<LegendElement> mElements;
	bool mFirstShow;
};

#endif // LEGEND_H
