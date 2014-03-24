#ifndef SELECTGRAPHICSWIDGET_H
#define SELECTGRAPHICSWIDGET_H

#include <QDialog>
#include "ui_selectgraphicswidget.h"
#include <QErrorMessage>
#include <QMessageBox>

class SelectGraphicsWidget : public QDialog
{
	Q_OBJECT

public:
	SelectGraphicsWidget(QWidget *parent = 0);
	~SelectGraphicsWidget();

signals:
	void selectedGraphics(int,int);

public slots:
	void comboBoxIndexChanged(int index);
	void ok();

private:
	void init();
	int indexInList(QString,QStringList);

private:
	Ui::SelectGraphicsWidget ui;
	// 每种交通信息对应的列表内容
	QStringList mList0;
	QStringList mList1;
	QStringList mList2;
	QStringList mList3;



};

#endif // SELECTGRAPHICSWIDGET_H
