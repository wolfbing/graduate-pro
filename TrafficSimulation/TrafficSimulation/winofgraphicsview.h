#ifndef WINOFGRAPHICSVIEW_H
#define WINOFGRAPHICSVIEW_H

#include <QMainWindow>
#include "ui_winofgraphicsview.h"
#include <QResizeEvent>
#include <QLabel>
#include "DbAdapter.h"
#include "selectgraphicswidget.h"

#include <QGraphicsScene>
#include "graphicsscene.h"

class GraphicsView;
class TurnRestrict;
class RoadPermission;
class TrafficVolume;
class Capability;
class Speed;

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
	void changeScene(int index1, int index2);
	void selectGraphics();
	void createDb();
	void selectDb();

protected:
	void showEvent(QShowEvent *);

private:
	void initStatusBar();
	void initActions();
	void initToolBar();
	void loadDataFromDb();
	
	

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
	GraphicsScene* mScene;
	SelectGraphicsWidget * mSelectWidget;
	// actions 
	QAction* mPrintAction;
	QAction* mSelectSceneAction;
	QAction* mCreateDbAction;
	QAction* mSelectDbAction;

	DbAdapter mDbAdapter;
    QList<Edge*> mEdgeDataList;
	QList<Node*> mNodeDataList;
	QList<BusRoute*> mBusRouteList;
	QList<TurnRestrict*> mTurnRestrictionList;
	QList<RoadPermission*> mRoadForbidList;
	QList<RoadPermission*> mRoadNumLimitList;
	QList<TrafficVolume*> mNodeTrafficVolumeList;
	QList<TrafficVolume*> mRoadTrafficVolumeList;
	QList<Capability*> mNodeCapabilityList;
	QList<Capability*> mRoadCapabilityList;
	QList<Speed*> mSpeedList;
};

#endif // WINOFGRAPHICSVIEW_H
