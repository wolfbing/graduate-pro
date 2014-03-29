#ifndef WINOFGRAPHICSVIEW_H
#define WINOFGRAPHICSVIEW_H

#include <QMainWindow>
#include "ui_winofgraphicsview.h"
#include <QResizeEvent>
#include <QLabel>

class WinOfGraphicsView : public QMainWindow
{
	Q_OBJECT

public:
	WinOfGraphicsView(QWidget *parent = 0);
	~WinOfGraphicsView();
	
signals:
	void sizeChange(int w, int h);

public slots:
	void updateStatus(QString);
	void clearTmpMsgFromStatus();
	void updatePermanentStatus(QString, QString);

protected:

private:
	void initStatusBar();
	

private:
	Ui::WinOfGraphicsView ui;
	// ×´Ì¬À¸
	QLabel* mStatusLabel1;
	QLabel* mStatusLabel2;
};

#endif // WINOFGRAPHICSVIEW_H
