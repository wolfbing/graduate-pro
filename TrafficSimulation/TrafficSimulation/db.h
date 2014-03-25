#ifndef DB_H
#define DB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QStringList>
#include <QDir>
#include <QVector>
#include <QPair>

#include "node.h"
#include "conn.h"

typedef NodeWithCoorNo Node;

class DB : public QObject
{
    Q_OBJECT
public:
    explicit DB(QObject *parent = 0);
    ~DB();

    QStringList createTablesAndFetchData();
    void setFileDir(QString dir);
    void clearTables();

    QList<QPair<QPointF*, QPointF*> > loadSec();
	QList<QPair<Node, Node> >* loadConn();
	QList<ConnWithCoorLevel>* loadConnWithLevel();
	QList<QString>* loadBusRoute();
	QHash<int,QPointF>* loadNodeById();
	QHash<int,QPointF>* loadNodeByNodeId();
	QVector<ConnWithNoPair>* loadConnByNo();
	QHash<int,int>* loadNodeIdToId();
	QList<QPointF>* loadNodes();


signals:

public slots:

private:
    // 创建各种表的函数, 内容其实都只是一句话
    void createNodeTable(QSqlQuery & query);
    void createConnTable(QSqlQuery & query);
    void createTrafficAreaTable(QSqlQuery & query);
    void createTurnRestrictTable(QSqlQuery & query);
    void createBusTable(QSqlQuery & query);
    void createForbidCoonTable(QSqlQuery & query);
    void createRestrictConnTable(QSqlQuery & query);
    // 从数据文件中获取数据然后存到数据库
    void fetchDataFromConnFile(QSqlQuery & query); // 这个貌似没用
    void fetchDataFromSectionFile(QSqlQuery & query);
    void fetchDataFromCoorFile(QSqlQuery & query);
    void fetchDataFromTrafficNode2OriNodeFile(QSqlQuery & query);
    void fetchDataFromTrafficNodeTypeFile(QSqlQuery & query);
    void fetchDataFromRestrictTurnFile(QSqlQuery & query);
    void fetchDataFromRoadTypeFile(QSqlQuery & query);
    void fetchDataFromForbiddenAreaFile(QSqlQuery & query);
    void fetchDataFromRestrictAreaFile(QSqlQuery & query);
    void fetchDataFromBusStopFile(QSqlQuery & query);
    void fetchDataFromBusNumFile(QSqlQuery & query);
    void fetchDataFromNodeStatisticsFile(QSqlQuery & query);
    void fetchDataFromRoadStatisticsFile(QSqlQuery & query);

    //
    void insertForbidAndRestrict(QSqlQuery & , QString , QString );

private:
    QSqlDatabase mDb;
    QString mConnName;
    QDir* mFileDir;

    // -------   static  area  ----------
    static const QString sDbType;
    static const QString sDbName;
    // 数据库表的名称
    static const QString sNodeTableName;
    static const QString sConnTableName;
    static const QString sTrafficAreaTableName;
    static const QString sTurnRestrictTableName;
    static const QString sBusTableName;
    static const QString sForbiddenConnTableName;
    static const QString sRestrictConnTableName;
    //数据文件名称
    static const QString sConnFileName;
    static const QString sSectionFileName;
    static const QString sCoorFileName;
    static const QString sTrafficNode2OriNodeFileName;
    static const QString sTrafficNodeTypeFileName;
    static const QString sRestrictTurnFileName;
    static const QString sRoadTypeFileName;
    static const QString sForbiddenAreaFileName;
    static const QString sRestrictAreaFileName;
    static const QString sBusStopFileName;
    static const QString sBusNumFileName;
    static const QString sNodeStatisticsFileName;
    static const QString sRoadStatisticsFileName;
    // 创建表的sql语句
    static const QString sSqlCreateNodeTable;
    static const QString sSqlCreateConnTable;
    static const QString sSqlCreateTrafficAreaTable;
    static const QString sSqlCreateTurnRestrictTable;
    static const QString sSqlCreateBusTable;
    static const QString sSqlCreateForbidConnTable;
    static const QString sSqlCreateRestrictConnTable;

};

#endif // DB_H
