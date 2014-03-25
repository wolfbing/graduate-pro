#ifndef WINOFGRAPHICSVIEW_H
#define WINOFGRAPHICSVIEW_H

#include <QMainWindow>
#include "ui_winofgraphicsview.h"
#include <QResizeEvent>

class WinOfGraphicsView : public QMainWindow
{
	Q_OBJECT

public:
	WinOfGraphicsView(QWidget *parent = 0);
	~WinOfGraphicsView();
	
signals:
	void sizeChange(int w, int h);

protected:
	

private:
	Ui::WinOfGraphicsView ui;
};

#endif // WINOFGRAPHICSVIEW_H
