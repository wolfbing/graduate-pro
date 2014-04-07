#ifndef WINOFGRAPHICSVIEW_H
#define WINOFGRAPHICSVIEW_H

#include <QMainWindow>
#include "ui_winofgraphicsview.h"
#include <QResizeEvent>
#include <QLabel>

#include <QGraphicsScene>

class GraphicsView;

class WinOfGraphicsView : public QMainWindow
{
	Q_OBJECT

public:
	WinOfGraphicsView(QWidget *parent = 0);
	~WinOfGraphicsView();
	
signals:
	void sizeChange(int w, int h);
	void print();

public slots:
	void updateStatus(QString);
	void clearTmpMsgFromStatus();
	void updatePermanentStatus(QString, QString);


protected:

private:
	void initStatusBar();
	void initActions();
	void initToolBar();

	
	

private:
	Ui::WinOfGraphicsView ui;
	// ×´Ì¬À¸
	QLabel* mStatusLabel1;
	QLabel* mStatusLabel2;
	// ¹¤¾ßÀ¸
	QToolBar* mToolBar;
	// view
	GraphicsView* mView;
	QGraphicsScene* tmpScene;
	// actions 
	QAction* mPrintAction;

};

#endif // WINOFGRAPHICSVIEW_H
