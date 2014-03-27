
#include <iostream>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QStringList>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QVariantList>
#include <QSqlError>

#include <QPointF>
#include <QPair>
#include <QVector>
#include <QHash>


#include "db.h"
#include "pathnotexistsexception.h"
#include "sqlqueryexception.h"


const QString DB::sDbType = "QSQLITE"; // 使用Sqlite3数据库
const QString DB::sDbName = "F:/GitHub/TrafficSimulation/TrafficSimulation/road.db";
// Table names
const QString DB::sNodeTableName = "road_node";
const QString DB::sConnTableName = "road_section";
const QString DB::sTrafficAreaTableName = "traffic_area";
const QString DB::sTurnRestrictTableName = "turn_restriction";
const QString DB::sBusTableName = "bus";
const QString DB::sForbiddenConnTableName = "forbid_section";
const QString DB::sRestrictConnTableName = "restric_section";
// file names
const QString DB::sConnFileName = "Conn.txt";
const QString DB::sSectionFileName = "Geom.txt";
const QString DB::sCoorFileName = "Coor.txt";
const QString DB::sTrafficNode2OriNodeFileName = "Chnn.txt";
const QString DB::sTrafficNodeTypeFileName = "Cont.txt";
const QString DB::sRestrictTurnFileName = "Nmanage.txt";
const QString DB::sRoadTypeFileName = "Lmanage.txt";
const QString DB::sForbiddenAreaFileName = "Rmanage1.txt";
const QString DB::sRestrictAreaFileName = "Rmanage2.txt";
const QString DB::sBusStopFileName = "Busstop.txt";
const QString DB::sBusNumFileName = "Busveh.txt";
const QString DB::sNodeStatisticsFileName = "Rtin.txt";
const QString DB::sRoadStatisticsFileName = "Rtil.txt";
// sql statements
const QString DB::sSqlCreateNodeTable =
        "create table  if not exists "+ DB::sNodeTableName +" ("+
        "id integer primary key,"+
        "node_id integer unique,"+
        "coor_x float,"+
        "coor_y float,"+
        "junction_type integer,"+
        "in_scale integer"+
        ");";
const QString DB::sSqlCreateConnTable =
        "create table if not exists "+ DB::sConnTableName + " (\
        id integer primary key,\
        start_node integer,\
        end_node integer,\
        sec_len float,\
        motor_driveway_width float,\
        non_motor_driveway_width float,\
        driveway_isolation integer,\
        road_level integer,\
        road_type integer,\
        traffic_type integer,\
        in_scale integer,\
        constraint section unique(start_node, end_node),"+
        "foreign key (start_node) references "+DB::sNodeTableName+"(id),"+
        "foreign key (end_node) references "+DB::sNodeTableName+"(id)"+
        ");";
const QString DB::sSqlCreateTrafficAreaTable =
        "create table if not exists "+ DB::sTrafficAreaTableName + " (\
        id integer primary key,\
        traffic_area_id integer unique,\
        node_id integer,"+
        "foreign key (node_id) references "+ DB::sNodeTableName +"(id)"+
        ");";
const QString DB::sSqlCreateBusTable =
        "create table if not exists "+ DB::sBusTableName +" (\
        id integer primary key,\
        route_id integer,\
        node_num integer,\
        nodes text,\
        vehicle integer,\
        equivalent integer\
        );";
const QString DB::sSqlCreateTurnRestrictTable =
        "create table if not exists "+ DB::sTurnRestrictTableName + "(\
        id integer primary key,\
        current_node integer,\
        from_node integer,\
        to_node integer,"+
        "foreign key (current_node) references "+DB::sTurnRestrictTableName+"(id),"+
        "foreign key (from_node) references "+DB::sTurnRestrictTableName+"(id),"+
        "foreign key (to_node) references "+DB::sTurnRestrictTableName+"(id)"+
        ");";
const QString DB::sSqlCreateForbidConnTable =
        "create table if not exists "+ DB::sForbiddenConnTableName + "(\
        id integer primary key,\
        road_id integer,\
        bike integer,\
        car integer,\
        motor integer,\
        taxi integer,\
        truck integer,\
        bus integer,"+
        "foreign key (road_id) references "+DB::sConnTableName+"(id)"+
        ");";
const QString DB::sSqlCreateRestrictConnTable =
        "create table if not exists "+ DB::sRestrictConnTableName +"(\
        id integer primary key,\
        road_id integer,\
        bike integer,\
        car integer,\
        motor integer,\
        taxi integer,\
        truck integer,\
        bus integer,"+
        "foreign key (road_id) references "+DB::sConnTableName+"(id)"+
        ");";


DB::DB(QObject *parent) :
    QObject(parent)
{
    this->mDb = QSqlDatabase::addDatabase(DB::sDbType);
    mDb.setDatabaseName(sDbName);
    if(!mDb.isOpen())
        mDb.open();
	mFileDir = NULL;
}

DB::~DB()
{
    if(mDb.isOpen())
        mDb.close();
    if(mFileDir != NULL)
        delete mFileDir;
}

// 将会搜索目录下的数据文件然后转存到数据库
// 返回搜索到的数据文件名列表
QStringList DB::createTablesAndFetchData()
{
    QSqlQuery query = QSqlQuery(mDb);
    QDir dir = *mFileDir;
    QStringList fileNameList;
    if(!dir.exists())
        throw new PathNotExistsException;
    mDb.transaction();
    // 转存文件时注意: 原始数据文件之间有依赖关系,
    // 在不进行数据库创建的时候, 这时所操作的文件应该是对上面的文件有所依赖的
    try{
        clearTables();
        if(dir.exists(DB::sCoorFileName)){
            createNodeTable(query);
            fetchDataFromCoorFile(query);
            fileNameList<<DB::sCoorFileName;
        }
        if(dir.exists(DB::sSectionFileName)){
            createConnTable(query);
            fetchDataFromSectionFile(query);
            fileNameList<<DB::sConnFileName;
        }
        if(dir.exists(DB::sTrafficNode2OriNodeFileName)){
            createTrafficAreaTable(query);
            fetchDataFromTrafficNode2OriNodeFile(query);
            fileNameList<<DB::sTrafficNode2OriNodeFileName;
        }
        if(dir.exists(DB::sTrafficNodeTypeFileName)){
            fetchDataFromTrafficNodeTypeFile(query);
            fileNameList<<DB::sTrafficNodeTypeFileName;
        }
        if(dir.exists(DB::sRestrictTurnFileName)){
            createTurnRestrictTable(query);
            fetchDataFromRestrictTurnFile(query);
            fileNameList<<DB::sRestrictTurnFileName;
        }
        if(dir.exists(DB::sRoadTypeFileName)){
            fetchDataFromRoadTypeFile(query);
            fileNameList<<DB::sRoadTypeFileName;
        }
        if(dir.exists(DB::sForbiddenAreaFileName)){
            createForbidCoonTable(query);
            fetchDataFromForbiddenAreaFile(query);
            fileNameList<<DB::sForbiddenAreaFileName;
        }
        if(dir.exists(DB::sRestrictAreaFileName)){
            createRestrictConnTable(query);
            fetchDataFromRestrictAreaFile(query);
            fileNameList<<DB::sRestrictAreaFileName;
        }
        if(dir.exists(DB::sBusStopFileName)){
            createBusTable(query);
            fetchDataFromBusStopFile(query);
            fileNameList<<DB::sBusStopFileName;
        }
        if(dir.exists(DB::sBusNumFileName)){
            fetchDataFromBusNumFile(query);
            fileNameList<<DB::sBusNumFileName;
        }
        if(dir.exists(DB::sNodeStatisticsFileName)){
            fetchDataFromNodeStatisticsFile(query);
            fileNameList<<DB::sNodeStatisticsFileName;
        }
        if(dir.exists(DB::sRoadStatisticsFileName)){
            fetchDataFromRoadStatisticsFile(query);
            fileNameList<<DB::sRoadStatisticsFileName;
        }

        mDb.commit();
        return fileNameList;
    }
    catch(QException &e){
        mDb.rollback();
        throw e;
    }
}


void DB::setFileDir(QString dir)
{
    mFileDir = new QDir(dir);
}


void DB::clearTables()
{
    QSqlQuery query(mDb);
    QStringList tables = mDb.tables();
    QString sql = "drop table if exists ";
    for(int i=0; i<tables.size();++i){
        if(!query.exec(sql + tables.at(i) +";")){
            throw new SqlQueryException("drop table failed");
        }
    }

}

QList<QPair<QPointF*, QPointF*> > DB::loadSec()
{
    QList<QPair<QPointF*,QPointF*> > secList;
    QList<QPair<int,int> > nodePairVec;
    QSqlQuery query(mDb);
    QString sql = "select start_node,end_node from "+DB::sConnTableName;
    if(!query.exec(sql))
    {
        QSqlError err = query.lastError();
        QString errText = err.text();
        throw new SqlQueryException(errText);
    }
    while(query.next()){
        nodePairVec.append(QPair<int,int>(query.value(0).toInt(),
                                 query.value(1).toInt()));

    }
    QString sql2 = "select id,coor_x,coor_y from "+DB::sNodeTableName;
    query.exec(sql2);
    QHash<int, QPointF* > points;
    while(query.next()){
        points.insert(query.value(0).toInt(),
                      new QPointF(query.value(1).toDouble(),
                                  query.value(2).toDouble()));
    }
    for(int i=0; i<nodePairVec.size(); ++i){
        secList.append(QPair<QPointF*,QPointF*>(points.value(nodePairVec.at(i).first),
                        points.value(nodePairVec.at(i).second)) );
    }
    return secList;

}


void DB::createNodeTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateNodeTable);
}


void DB::createConnTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateConnTable);
}


void DB::createTrafficAreaTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateTrafficAreaTable);
}


void DB::createTurnRestrictTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateTurnRestrictTable);
}


void DB::createBusTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateBusTable);
}


void DB::createForbidCoonTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateForbidConnTable);
}


void DB::createRestrictConnTable(QSqlQuery &query)
{
    query.exec(DB::sSqlCreateRestrictConnTable);
}


void DB::fetchDataFromSectionFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sSectionFileName))
        throw PathNotExistsException("cannot find file "+DB::sSectionFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sSectionFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int startNode, endNode;
        double secLen, motorDrivewayWidth, nonMotorDriveWayWidth;
        int isolateType, roadLevel;
        int NUM_ONCE = 100;
        while(!in.atEnd()){
            int num = 0;
            QString sql = "insert into "+DB::sConnTableName+
                    "(start_node, end_node, sec_len, motor_driveway_width,"+
                    "non_motor_driveway_width, driveway_isolation, road_level) "+
                    "values ("+
                    "(select id from "+DB::sNodeTableName+" where node_id=?),"+ //外键, 下同
                    "(select id from "+DB::sNodeTableName+" where node_id=?),"+
                    "?,?,?,?,?)";
            query.prepare(sql);
            QVariantList startNodes, endNodes, secLens;
            QVariantList motorDrivewayWidths,nonMotorDriveWayWidths;
            QVariantList isolateTypes, roadLevels;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>startNode>>endNode>>secLen>>motorDrivewayWidth
                    >>nonMotorDriveWayWidth>>isolateType>>roadLevel;
                if(startNode!=0 && endNode!=0){ // 目的一是数据唯一性, 二是过滤0数据
                    startNodes.append(startNode);
                    endNodes.append(endNode);
                    secLens.append(secLen);
                    motorDrivewayWidths.append(motorDrivewayWidth);
                    nonMotorDriveWayWidths.append(nonMotorDriveWayWidth);
                    isolateTypes.append(isolateType);
                    roadLevels.append(roadLevel);
                    num++;
                }
            }
            query.bindValue(0, startNodes);
            query.bindValue(1, endNodes);
            query.bindValue(2, secLens);
            query.bindValue(3, motorDrivewayWidths);
            query.bindValue(4, nonMotorDriveWayWidths);
            query.bindValue(5, isolateTypes);
            query.bindValue(6, roadLevels);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }

        }

        file->close();
        delete file;


    }
}


void DB::fetchDataFromCoorFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sCoorFileName))
        throw new PathNotExistsException("cannot find file"+DB::sCoorFileName);
    QString filePath = mFileDir->absoluteFilePath(DB::sCoorFileName);
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly)){
        QTextStream in(&file);
        while(!in.atEnd()){
            int node_id;
            double coor_x, coor_y;
            int num = 0; // sqlite3要求不能一次执行大于500次的操作,
                         // 这里限制在每次插入500个数据,(一个一个插入太慢了！！)
            int const INSERT_NUM = 500;
            QString sql = "insert into "+DB::sNodeTableName+
                    " (node_id, coor_x, coor_y) values (?,?,?)";
            query.prepare(sql);
            QVariantList node_ids;
            QVariantList coor_xs;
            QVariantList coor_ys;
            while(!in.atEnd() && num<INSERT_NUM){
                in>>node_id>>coor_x>>coor_y;
                if(node_id!=0){ // 过滤掉空行产生的0数据
                    node_ids<<node_id;
                    coor_xs<<coor_x;
                    coor_ys<<coor_y;
                }
            }
            //findSameNum(node_ids);
            query.addBindValue(node_ids);
            query.addBindValue(coor_xs);
            query.addBindValue(coor_ys);
            mDb.transaction();
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                mDb.rollback();
                throw new SqlQueryException("处理文件"+DB::sCoorFileName+"时出错,"+
                                            "sqlerror:"+err.text());
            }
            mDb.commit();


        }
        file.close();
    }

}


/**
 * @brief DB::fetchDataFromTrafficNode2OriNodeFile
 * @param query
 * @exceptions PathNotExistsException, SqlQueryException
 */
void DB::fetchDataFromTrafficNode2OriNodeFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sTrafficNode2OriNodeFileName))
        throw new PathNotExistsException("cannot find file "+
                                         DB::sTrafficNode2OriNodeFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sTrafficNode2OriNodeFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int tmp; in>>tmp; // 第一行数据不需要
        int trafficId, nodeId;
        int NUM_ONCE = 200;
        QString sql = "insert into "+DB::sTrafficAreaTableName+" (traffic_area_id, node_id) "+
                "values(?,"+
                "(select id from "+DB::sNodeTableName+" where node_id=?));";
        while(!in.atEnd()){
            int num =0;
            query.prepare(sql);
            QVariantList trafficIds, nodeIds;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>trafficId>>nodeId;
                if(trafficId!=0){
                    trafficIds.append(trafficId);
                    nodeIds.append(nodeId);
                    num++;
                }
            }
            query.bindValue(0, trafficIds);
            query.bindValue(1, nodeIds);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }

        }

        file->close();
    }
    delete file;

}


/**
 * @brief DB::fetchDataFromTrafficNodeTypeFile
 * @param query
 * @exceptions PathNotExistsException, SqlQueryException
 */
void DB::fetchDataFromTrafficNodeTypeFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sTrafficNodeTypeFileName))
        throw new PathNotExistsException("cannot find file "
                                         +DB::sTrafficNodeTypeFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sTrafficNodeTypeFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int nodeId, nodeType;
        QString sql = "update "+DB::sNodeTableName+" set junction_type=? where node_id=?;";
        int NUM_ONCE = 500;
        while(!in.atEnd()){
            int num = 0;
            QVariantList nodeIds, nodeTypes;
            query.prepare(sql);
            while(!in.atEnd() && num<NUM_ONCE){
                in>>nodeId>>nodeType;
                if(nodeId!=0){
                    nodeIds.append(nodeId);
                    nodeTypes.append(nodeType);
                    num++;
                }
            }
            query.bindValue(0, nodeTypes);
            query.bindValue(1, nodeIds);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }

        }
        file->close();
    }

    delete file;

}


/**
 * @brief DB::fetchDataFromRestrictTurnFile
 * @param query
 * @exceptions PathNotExistsException, SqlQueryException
 */
void DB::fetchDataFromRestrictTurnFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sRestrictTurnFileName))
        throw new PathNotExistsException("cannot find file "
                                         + DB::sRestrictTurnFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sRestrictTurnFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int currNode, fromNode, toNode, tmp;
        QString sql = "insert into "+DB::sTurnRestrictTableName+
                " (current_node, from_node, to_node) values ("+
                "(select id from "+DB::sNodeTableName+" where node_id=?),"+
                "(select id from "+DB::sNodeTableName+" where node_id=?),"+
                "(select id from "+DB::sNodeTableName+" where node_id=?)"+
                ");";
        int NUM_ONCE = 100;
        in>>tmp; // 略去第一行数据
        while(!in.atEnd()){
            int num = 0;
            QVariantList currNodes, fromNodes, toNodes;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>currNode>>tmp>>tmp>>fromNode>>tmp>>toNode; // 有几个没用的数据
                if(currNode!=0){
                    currNodes.append(currNode);
                    fromNodes.append(fromNode);
                    toNodes.append(toNode);
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0, currNodes);
            query.bindValue(1, fromNodes);
            query.bindValue(2, toNodes);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }
        }

        file->close();
    }
    delete file;
}


void DB::fetchDataFromRoadTypeFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sRoadTypeFileName))
        throw new PathNotExistsException("cannot find file "+
                                         DB::sRoadTypeFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sRoadTypeFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        QString sql = "update "+DB::sConnTableName+
                " set road_type=?,traffic_type=?"+
                " where start_node=(select id from "+DB::sNodeTableName+" where node_id=?) "+
                "and end_node=(select id from "+DB::sNodeTableName+" where node_id=?);";
        int startNode, endNode, roadType, trafficType;
        int NUM_ONCE = 500;
        while(!in.atEnd()){
            int num = 0;
            QVariantList startNodes, endNodes, roadTypes, trafficTypes;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>startNode>>endNode>>roadType>>trafficType;
                if(startNode!=0 && endNode!=0){
                    startNodes.append(startNode);
                    endNodes.append(endNode);
                    roadTypes.append(roadType);
                    trafficTypes.append(trafficType);
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0, roadTypes);
            query.bindValue(1,trafficTypes);
            query.bindValue(2,startNodes);
            query.bindValue(3,endNodes);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw SqlQueryException(errText);
            }
        }


        file->close();
    }
    delete file;
}



void DB::insertForbidAndRestrict(QSqlQuery & query, QString tbName, QString fileName){
    if(!mFileDir->exists(fileName))
        throw new PathNotExistsException("cannot find file "
                                         +fileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(fileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int startNode, endNode;
        int bike, car, motor, taxi, truck, bus;
        int NUM_ONCE = 200;
        QString sql = "insert into "+tbName+
                " (road_id, bike, car, motor, taxi, truck, bus) "+
                " values("+
                "(select id from "+DB::sConnTableName+
                " where start_node=(select id from "+DB::sNodeTableName+" where node_id=?) "+
                " and end_node=(select id from "+DB::sNodeTableName+" where node_id=?)),"+
                "?,?,?,?,?,?);";
        QString tmp;
        in>>tmp>>tmp>>tmp>>tmp>>tmp>>tmp>>tmp>>tmp; // 略过第一行的没用数据
        while(!in.atEnd()){
            QVariantList startNodes, endNodes;
            QVariantList bikes, cars, motors, taxis, trucks, buses;
            int num = 0;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>startNode>>endNode>>bike>>car>>motor>>taxi>>truck>>bus;
                if(startNode!=0 && endNode!=0){
                    startNodes.append(startNode);
                    endNodes.append(endNode);
                    bikes.append(bike);
                    cars.append(car);
                    motors.append(motor);
                    taxis.append(taxi);
                    trucks.append(truck);
                    buses.append(bus);
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0,startNodes);
            query.bindValue(1, endNodes);
            query.bindValue(2,bikes);
            query.bindValue(3,cars);
            query.bindValue(4,motors);
            query.bindValue(5,taxis);
            query.bindValue(6,trucks);
            query.bindValue(7,buses);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }
        }

        file->close();
    }

    delete file;

}



void DB::fetchDataFromForbiddenAreaFile(QSqlQuery &query)
{
    insertForbidAndRestrict(query, DB::sForbiddenConnTableName,
                            DB::sForbiddenAreaFileName);
}


void DB::fetchDataFromRestrictAreaFile(QSqlQuery &query)
{
    insertForbidAndRestrict(query, DB::sRestrictConnTableName,
                            DB::sRestrictAreaFileName);

}


void DB::fetchDataFromBusStopFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sBusStopFileName))
        throw new PathNotExistsException("cannot find file "+
                                         DB::sBusStopFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sBusStopFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        QString tmp;
        in>>tmp; // 略过第一行的没用数据
        QString sql = "insert into "+DB::sBusTableName+
                " (route_id, node_num, nodes) values (?,?,?);";
        int NUM_ONCE = 500;
        int routeId = 0;
        int nodeNum;
        QString nodeId;
        while(!in.atEnd()){
            int num = 0;
            QVariantList route_ids, node_nums, nodess;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>tmp>>nodeNum;
                if(tmp!=""){
                    routeId++;
                    QStringList routeNodes;
                    for(int i=0; i<nodeNum;++i){
                        in>>nodeId;
                        routeNodes.append(nodeId);
                    }
                    route_ids.append(routeId);
                    node_nums.append(nodeNum);
                    nodess.append(routeNodes.join(","));
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0, route_ids);
            query.bindValue(1, node_nums);
            query.bindValue(2, nodess);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }

        }
        file->close();
    }

    delete file;

}


void DB::fetchDataFromBusNumFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sBusNumFileName))
        throw new PathNotExistsException("cannot find file "
                                         +DB::sBusNumFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sBusNumFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream in(file);
        int tmp;
        in>>tmp; // 略过第一行没用的数据
        QString sql = "update "+DB::sBusTableName +
                " set vehicle=?,equivalent=? "+
                " where route_id=?;";
        int NUM_ONCE = 500;
        int routeId, vehicle, equivalent;
        while(!in.atEnd()){
            int num = 0;
            QVariantList routeIds, vehicles, equivalents;
            while(!in.atEnd() && num<NUM_ONCE){
                in>>routeId>>vehicle>>equivalent;
                if(routeId!=0){
                    routeIds.append(routeId);
                    vehicles.append(vehicle);
                    equivalents.append(equivalent);
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0, vehicles);
            query.bindValue(1,equivalents);
            query.bindValue(2,routeIds);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }
        }
        file->close();
    }

    delete file;

}


void DB::fetchDataFromNodeStatisticsFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sNodeStatisticsFileName))
        throw new PathNotExistsException("cannot find file "
                                         +DB::sNodeStatisticsFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sNodeStatisticsFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream instream(file);
        int nodeId, in;
        QString sql = "update "+DB::sNodeTableName+
                " set in_scale=? where node_id=?;";
        int NUM_ONCE = 500;
        while(!instream.atEnd()){
            int num = 0;
            QVariantList nodeIds, ins;
            while(!instream.atEnd() && num<NUM_ONCE){
                instream>>nodeId>>in;
                if(nodeId!=0){
                    nodeIds.append(nodeId);
                    ins.append(in);
                    num++;
                }
            }
            query.prepare(sql);
            query.bindValue(0, ins);
            query.bindValue(1,nodeIds);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }
        }

        file->close();
    }

    delete file;

}


void DB::fetchDataFromRoadStatisticsFile(QSqlQuery &query)
{
    if(!mFileDir->exists(DB::sRoadStatisticsFileName))
        throw new PathNotExistsException("cannot find file "
                                         + DB::sRoadStatisticsFileName);
    QFile* file = new QFile(mFileDir->absoluteFilePath(DB::sRoadStatisticsFileName));
    if(file->open(QIODevice::ReadOnly)){
        QTextStream instream(file);
        QString sql = "update "+DB::sConnTableName+
                " set in_scale=? where "+
                "start_node=(select id from "+DB::sNodeTableName+" where node_id=?) "+
                "and end_node=(select id from "+DB::sNodeTableName+" where node_id=?);";
        int NUM_ONCE=500;
        int startNode, endNod, in;
        while(!instream.atEnd()){
            QVariantList startNodes, endNodes, ins;
            int num=0;
            while(!instream.atEnd() && num<NUM_ONCE){
                instream>>startNode>>endNod>>in;
                if(startNode!=0 && endNod!=0){
                    startNodes.append(startNode);
                    endNodes.append(endNod);
                    ins.append(in);
                }

            }
            query.prepare(sql);
            query.bindValue(0, ins);
            query.bindValue(1, startNodes);
            query.bindValue(2, endNodes);
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                QString errText = err.text();
                throw new SqlQueryException(errText);
            }
        }

        file->close();
    }

    delete file;

}

QList<QPair<Node, Node> >* DB::loadConn()
{
	//QList<QPair<QPointF*,QPointF*> > secList;
	QList<QPair<Node,Node> >* secList = new QList<QPair<Node,Node> >;
	QList<QPair<int,int> > nodePairVec;
	QSqlQuery query(mDb);
	QString sql = "select start_node,end_node from "+DB::sConnTableName;
	if(!query.exec(sql))
	{
		QSqlError err = query.lastError();
		QString errText = err.text();
		throw new SqlQueryException(errText);
	}
	while(query.next()){
		nodePairVec.append(QPair<int,int>(query.value(0).toInt(),
			query.value(1).toInt()));

	}
	QString sql2 = "select id,node_id,coor_x,coor_y from "+DB::sNodeTableName;
	query.exec(sql2);
	QHash<int, Node> points;
	while(query.next()){
		points.insert(query.value(0).toInt(),
			Node(QPointF(query.value(2).toDouble(),	query.value(3).toDouble()),query.value(1).toInt()));
	}
	for(int i=0; i<nodePairVec.size(); ++i){
		secList->append(QPair<Node,Node>(points.value(nodePairVec.at(i).first),
			points.value(nodePairVec.at(i).second)) );
	}
	return secList;
}

QList<ConnWithCoorLevel>* DB::loadConnWithLevel()
{
	QList<ConnWithCoorLevel >* connList = new QList<ConnWithCoorLevel>;
	QSqlQuery query(mDb);

	// 载入坐标
	QString sql2 = "select id,coor_x,coor_y from "+DB::sNodeTableName;
	query.exec(sql2);
	QHash<int, QPointF> points;
	while(query.next()){
		points.insert(query.value(0).toInt(),
			QPointF(query.value(1).toDouble(),	query.value(2).toDouble()));
	}
	// 载入道路
	QString sql = "select start_node,end_node,road_level from "+DB::sConnTableName;
	if(!query.exec(sql))
	{
		QSqlError err = query.lastError();
		QString errText = err.text();
		throw new SqlQueryException(errText);
	}
	while(query.next()){
		int p1 = query.value(0).toInt();
		int p2 = query.value(1).toInt();
		connList->append(ConnWithCoorLevel(
			QPair<QPointF,QPointF>(points.value(p1),points.value(p2)), 
			query.value(2).toInt()));
	}
	
	return connList;
}

QList<QString>* DB::loadBusRoute()
{
	QList<QString>* routes = new QList<QString>;
	QSqlQuery query(mDb);

	QString sql = "select nodes from " + sBusTableName ;
	query.exec(sql);
	while (query.next())
	{
		routes->append(query.value(0).toString());
	}
	return routes;
}

QHash<int,QPointF>* DB::loadNodeById()
{
	QSqlQuery query(mDb);

	// 载入坐标
	QString sql2 = "select id,coor_x,coor_y from "+DB::sNodeTableName;
	query.exec(sql2);
	QHash<int, QPointF>* points = new QHash<int, QPointF>;
	while(query.next()){
		points->insert(query.value(0).toInt(),
			QPointF(query.value(1).toDouble(),	query.value(2).toDouble()));
	}
	return points;
}

QVector<ConnWithNoPair>* DB::loadConnByNo()
{
	QSqlQuery query(mDb);
	QString sql = "select start_node,end_node from "+DB::sConnTableName;
	if(!query.exec(sql))
	{
		QSqlError err = query.lastError();
		QString errText = err.text();
		throw new SqlQueryException(errText);
	}
	//QList<QPair<int,int> >* li = new QList<QPair<int,int> >;
	QVector<ConnWithNoPair>* vec = new QVector<ConnWithNoPair>;
	vec->append(ConnWithNoPair(1,2));
	vec->append(ConnWithNoPair(3,4));
	//QVector<ConnWithNoPair>* vec = new QVector<ConnWithNoPair>;
	while(query.next()){
		int p1 = query.value(0).toInt();
		int p2 = query.value(1).toInt();
		vec->append(ConnWithNoPair(p1,p2));
	}
	return vec;
}

QHash<int,QPointF>* DB::loadNodeByNodeId()
{
	QSqlQuery query(mDb);

	// 载入坐标
	QString sql2 = "select node_id,coor_x,coor_y from "+DB::sNodeTableName;
	query.exec(sql2);
	QHash<int, QPointF>* points = new QHash<int, QPointF>;
	while(query.next()){
		points->insert(query.value(0).toInt(),
			QPointF(query.value(1).toDouble(),	query.value(2).toDouble()));
	}
	return points;
}

QHash<int,int>* DB::loadNodeIdToId()
{
	QHash<int,int>* hash = new QHash<int,int>;
	QSqlQuery query(mDb);

	// 载入坐标
	QString sql = "select id, node_id from "+DB::sNodeTableName;
	query.exec(sql);
	while(query.next()){
		hash->insert(query.value(1).toInt(), query.value(0).toInt());
	}
	return hash;
}

QList<Node>* DB::loadNodes()
{
	QList<Node>* nodeList = new QList<Node>;
	QSqlQuery query(mDb);

	// 载入坐标
	QString sql = "select node_id, coor_x, coor_y from "+DB::sNodeTableName;
	query.exec(sql);
	while(query.next()){
		nodeList->append(Node(
			QPointF( query.value(1).toInt(), query.value(2).toInt() ), 
			query.value(0).toInt() )  );
	}
	return nodeList;
}

QList<ConnWithCoorPair>* DB::loadConns()
{
	QList<ConnWithCoorPair>* secList = new QList<ConnWithCoorPair>;
	QList<QPair<int,int> > nodePairVec;
	QSqlQuery query(mDb);
	QString sql = "select start_node,end_node from "+DB::sConnTableName;
	if(!query.exec(sql))
	{
		QSqlError err = query.lastError();
		QString errText = err.text();
		throw new SqlQueryException(errText);
	}
	while(query.next()){
		nodePairVec.append(QPair<int,int>(query.value(0).toInt(),
			query.value(1).toInt()));

	}
	QString sql2 = "select id,coor_x,coor_y from "+DB::sNodeTableName;
	query.exec(sql2);
	QHash<int, QPointF> points;
	while(query.next()){
		points.insert(query.value(0).toInt(),
			QPointF(query.value(1).toDouble(),	query.value(2).toDouble() )  );
	}
	for(int i=0; i<nodePairVec.size(); ++i){
		secList->append(ConnWithCoorPair(points.value(nodePairVec.at(i).first),
			points.value(nodePairVec.at(i).second) )  );
	}
	return secList;
}












