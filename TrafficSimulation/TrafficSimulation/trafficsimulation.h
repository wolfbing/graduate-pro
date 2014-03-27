#ifndef TRAFFICSIMULATION_H
#define TRAFFICSIMULATION_H

#include <QtWidgets/QMainWindow>
#include "ui_trafficsimulation.h"
#include "selectgraphicswidget.h"

/*
- 控制各种交通图的切换
*/
class TrafficSimulation : public QMainWindow
{
	Q_OBJECT

public:
	TrafficSimulation(QWidget *parent = 0);
	~TrafficSimulation();

protected:
	void paintEvent(QPaintEvent *);

public slots:
	void showSelectGraphicsDialog();
	void changeGraphics(int,int);

private:
	void initActions();
	void initToolBar();

private:
	Ui::TrafficSimulationClass ui;
	// action
	QAction* mSelectGraphicsAction;
	QAction* mPrintAction;
	// 
	bool mNoGraphics;
	int mCurrentComIndex;
	int mCurrentListIndex;
	// toolbar
	QToolBar* mToolBar;
	// 选择交通图的对话框
	SelectGraphicsWidget* mSelectGraphicsDialog;
	// 各种图
};

#endif // TRAFFICSIMULATION_H
