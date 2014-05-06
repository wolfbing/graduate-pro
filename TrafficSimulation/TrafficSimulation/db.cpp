
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
#include "commonexception.h"
#include "sqlqueryexception.h"
#include "Edge.h"
#include "structsfordb.h"
#include "node.h"
#include "BusRoute.h"
#include "TurnRestrict.h"
#include "RoadPermission.h"
#include "TrafficVolume.h"
#include "Capability.h"
#include "Speed.h"


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
const QString DB::sNodeVolumeTableName = "node_volume";
const QString DB::sRoadVolumeTableName = "road_volume";
const QString DB::sNodeCapabilityTableName = "node_capability";
const QString DB::sRoadCapabilityTableName = "road_capability";
const QString DB::sSpeedTableName = "speed";
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
///// 交通量
const QString DB::sNodeMotorVolumeFileName = "node-v.veh";
const QString DB::sNodeNonMotorVolumeFileName = "node-v.bic";
const QString DB::sNodeBusVolumeFileName = "node-v.bus";
const QString DB::sNodeCarVolumeFileName = "node-v.car";
const QString DB::sNodeMotorbikeVolumeFileName = "node-v.mot";
const QString DB::sNodeTaxiVolumeFileName = "node-v.tax";
const QString DB::sNodeTruckVolumeFileName = "node-v.trk";
///// 交通承载量
const QString DB::sNodeMotorCapabilityFileName = "node-vc.veh";
const QString DB::sNodeNonMotorCapabilityFileName = "node-vc.bic";
const QString DB::sRoadMotorCapabilityFileName = "link-vc.veh";
const QString DB::sRoadNonMotorCapabilityFileName = "link-vc.bic";
const QString DB::sSpeedFileName = "speed.veh";

const QString DB::sRoadMotorVolumeFileName = "link-v.veh";
const QString DB::sRoadNonMotorVolumeFileName = "link-v.bic";
const QString DB::sRoadBusVolumeFileName = "link-v.bus";
const QString DB::sRoadCarVolumeFileName = "link-v.car";
const QString DB::sRoadMotorbikeVolumeFileName = "link-v.mot";
const QString DB::sRoadTaxiVolumeFileName = "link-v.tax";
const QString DB::sRoadTruckVolumeFileName = "link-v.trk";
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
const QString DB::sSqlCreateNodeVolumeTable = 
	"create table if not exists "+DB::sNodeVolumeTableName+" ( "
	+ "id integer primary key,"
	+ "node_id integer,"
	+ "motor float,"
	+ "non_motor float,"
	+ "car float,"
	+ "bus float,"
	+ "motorbike float,"
	+ "truck float,"
	+ "taxi float,"
	+ "foreign key (node_id) references "+DB::sNodeTableName+"(id)"
	+");"
	;
const QString DB::sSqlCreateRoadVolumeTable = 
	"create table if not exists "+DB::sRoadVolumeTableName+ " ("
	+ "id integer primary key,"
	+ "road_id integer,"
	+ "motor float,"
	+ "non_motor float,"
	+ "car float,"
	+ "bus float,"
	+ "motorbike float,"
	+ "truck float,"
	+ "taxi float,"
	+ "foreign key (road_id) references "+DB::sConnTableName+"(id)"
	+");"
	;
const QString DB::sSqlCreateNodeCapabilityTable = 
	"create table if not exists "+DB::sNodeCapabilityTableName+" ("
	+"id integer primary key,"
	+"node_id integer,"
	+"motor float,"
	+"non_motor float,"
	+"foreign key (node_id) references "+DB::sNodeTableName+"(id)"
	+");";

const QString DB::sSqlCreateRoadCapabilityTable = 
	"create table if not exists "+DB::sRoadCapabilityTableName+" ("
	+"id integer primary key,"
	+"road_id integer,"
	+"motor float,"
	+"non_motor float,"
	+"foreign key (road_id) references "+DB::sConnTableName+"(id)"
	+");";

const QString DB::sSqlCreateSpeedTable = 
	"create table if not exists "+DB::sSpeedTableName+" ("
	+"road_id integer primary key,"
	+"speed float,"
	+"foreign key (road_id) references "+ DB::sConnTableName+"(id)"
	+");";



DB::DB(QObject *parent) :
    QObject(parent)
{
	mFileDir = NULL;
}

DB::~DB()
{
    if(mFileDir != NULL)
        delete mFileDir;
}

// 将会搜索目录下的数据文件然后转存到数据库
// 返回搜索到的数据文件名列表
void DB::createTablesAndFetchData()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType, "create_db");
	QDir dbDir("./");
	if (!dbDir.exists("./db/"))
	{
		dbDir.mkdir("./db/");
	}
	db.setDatabaseName("./db/"+ mCreateDbName);
	db.open();
    QSqlQuery query = QSqlQuery(db);
    QDir dir = *mFileDir;
    //QStringList fileNameList;
    if(!dir.exists())
        throw PathNotExistsException("directory does not exist!");
	try
	{
		db.transaction();
		// 转存文件时注意: 原始数据文件之间有依赖关系,
		// 在不进行数据库创建的时候, 这时所操作的文件应该是对上面的文件有所依赖的
		clearTables(db);
		createNodeTable(query);
		createConnTable(query);
		createTrafficAreaTable(query);
		createTurnRestrictTable(query);
		createForbidCoonTable(query);
		createRestrictConnTable(query);
		createBusTable(query);
		createNodeVolumeTable(query);
		createRoadVolumeTable(query);
		createNodeCapabilityTable(query);
		createRoadCapabilityTable(query);
		createSpeedTable(query);

		fetchDataFromCoorFile(query);
		fetchDataFromSectionFile(query);
		fetchDataFromTrafficNode2OriNodeFile(query);
		fetchDataFromTrafficNodeTypeFile(query);
		fetchDataFromRestrictTurnFile(query);
		fetchDataFromRoadTypeFile(query);
		fetchDataFromForbiddenAreaFile(query);
		fetchDataFromRestrictAreaFile(query);
		fetchDataFromBusStopFile(query);
		fetchDataFromBusNumFile(query);
		fetchDataFromNodeStatisticsFile(query);
		fetchDataFromRoadStatisticsFile(query);
		fetchDataFromNodeVolumeFiles(query);
		fetchDataFromRoadVolumeFiles(query);
		fetchDataFromNodeCapabilityFile(query);
		fetchDataFromRoadCapabilityFile(query);
		fetchDataFromSpeedFile(query);
	}
	catch(PathNotExistsException&e){
		db.rollback();
		db.close();
		throw e;
	}
	catch(CommonException&e){
		db.rollback();
		db.close();
		throw e;
	}
	catch (QException& e)
	{
		db.rollback();
		db.close();
		throw e;
	}
	db.commit();
	db.close();

}


void DB::setFileDir(QString dir)
{
    mFileDir = new QDir(dir);
}


void DB::clearTables(QSqlDatabase& db)
{
	if(!db.isOpen())
		db.open();
    QSqlQuery query(db);
    QStringList tables = db.tables();
    QString sql = "drop table if exists ";
    for(int i=0; i<tables.size();++i){
        if(!query.exec(sql + tables.at(i) +";")){
            throw new SqlQueryException("drop table failed");
        }
    }

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
        throw PathNotExistsException("cannot find file"+DB::sCoorFileName);
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
            if(!query.execBatch()){
                QSqlError err = query.lastError();
                throw new SqlQueryException("处理文件"+DB::sCoorFileName+"时出错,"+
                                            "sqlerror:"+err.text());
            }

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
        throw PathNotExistsException("cannot find file "+
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
        throw PathNotExistsException("cannot find file "
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
        throw PathNotExistsException("cannot find file "
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
        throw PathNotExistsException("cannot find file "+
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
        throw PathNotExistsException("cannot find file "
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
        throw PathNotExistsException("cannot find file "+
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
        throw PathNotExistsException("cannot find file "
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
        throw PathNotExistsException("cannot find file "
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
        throw PathNotExistsException("cannot find file "
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

QList<Node*> DB::loadNodes()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QList<Node*> nodeList;
	QSqlQuery query(db);

	// 载入坐标
	QString sql = "select node_id, coor_x, coor_y, junction_type, in_scale,id from "+DB::sNodeTableName;
	query.exec(sql);
	Node * tmpNode;
	while(query.next()){
		tmpNode = new Node;
		tmpNode->setCoor(QPointF( query.value(1).toInt(), query.value(2).toInt() ) )
			.setNo(query.value(0).toInt()).setJunctionType(query.value(3).toInt())
			.setInScale(query.value(4).toBool()).setId(query.value(5).toInt());
		nodeList << tmpNode;
	}
	db.commit();
	db.close();
	return nodeList;
}


QList<Edge*> DB::loadEdges()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QList<Edge*> edgeList; // 用于返回值的edge集合
	QSqlQuery query(db);
	QString sql = QString("select start_node,end_node,road_level,sec_len,")+
		"motor_driveway_width,non_motor_driveway_width,driveway_isolation, "+
		"road_type,traffic_type,in_scale,id"+" from " + DB::sConnTableName;
	if(!query.exec(sql))
	{
		QSqlError err = query.lastError();
		QString errText = err.text();
		throw new SqlQueryException(errText);
	}
	Edge * tmpEdge;
	while(query.next()){
		tmpEdge = new Edge;
		tmpEdge->setSourceNodeId(query.value(0).toInt()).setDestNodeId(query.value(1).toInt())
			.setRoadLevel(query.value(2).toInt())
			.setLength(query.value(3).toReal()).setMotorWayWidth(query.value(4).toReal())
			.setNonMotorWayWidth(query.value(5).toReal()).setWayIsolate(query.value(6).toBool())
			.setRoadType(query.value(7).toInt()).setTrafficType(query.value(8).toInt())
			.setInScale(query.value(9).toBool()).setId(query.value(10).toInt());
		edgeList << tmpEdge;
	} 
	db.commit();
	db.close();
	return edgeList;
}

QList<BusRoute*> DB::loadBusRoutes()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QList<BusRoute*> busRouteList;
	QSqlQuery query(db);
	QString sql = QString("select id,route_id,node_num,nodes,vehicle,equivalent ")
		+ "from " + sBusTableName;
	BusRoute* route;
	QStringList strList;
	if (query.exec(sql))
	{
		while (query.next())
		{
			route = new BusRoute;
			route->setId(query.value(0).toInt()).setRouteId(query.value(1).toInt())
				.setStopNum(query.value(2).toInt()).setVehicle(query.value(4).toInt())
				.setCarEquivalent(query.value(5).toReal());
			strList = query.value(3).toString().split(",");
			QList<int> stops;
			for (int i=0; i<strList.size(); ++i)
			{
				stops << strList.at(i).toInt();
			}
			route->setStops(stops);
			busRouteList << route;
		}
		
	}
	db.commit();
	db.close();
	return busRouteList;
}

QList<TurnRestrict*> DB::loadTurnRestrictions()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QList<TurnRestrict*> restrictionList;
	QSqlQuery query(db);
	QString sql = "select current_node, from_node, to_node from "+sTurnRestrictTableName;
	TurnRestrict* restr;
	if (query.exec(sql))
	{
		while (query.next())
		{
			restr = new TurnRestrict;
			restr->setCurrentNodeNo(query.value(0).toInt());
			restr->setFromNodeNo(query.value(1).toInt());
			restr->setToNodeNo(query.value(2).toInt());
			restrictionList << restr;
		}
	}
	db.commit();
	db.close();
	return restrictionList;
}

QList<RoadPermission*> DB::loadTrafficForbid()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QSqlQuery query(db);
	QString sql = "select road_id, bike, car, motor, taxi, truck, bus from "
		+ sForbiddenConnTableName;
	QList<RoadPermission*> forbidList;
	RoadPermission* tmpForbid;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpForbid = new RoadPermission;
			tmpForbid->setRoadId(query.value(0).toInt()).setPermitBike(query.value(1).toInt())
				.setPermitCar(query.value(2).toInt()).setPermitMotor(query.value(3).toInt())
				.setPermitTaxi(query.value(4).toInt()).setPermitTruck(query.value(5).toInt())
				.setPermitBus(query.value(6).toInt());
			forbidList << tmpForbid;
		}
	}
	db.commit();
	db.close();
	return forbidList;
}

QList<RoadPermission*> DB::loadTrafficNumLimit()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	db.transaction();
	QSqlQuery query(db);
	QString sql = "select road_id, bike, car, motor, taxi, truck, bus from "
		+ sRestrictConnTableName;
	QList<RoadPermission*> forbidList;
	RoadPermission* tmpForbid;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpForbid = new RoadPermission;
			tmpForbid->setRoadId(query.value(0).toInt()).setPermitBike(query.value(1).toInt())
				.setPermitCar(query.value(2).toInt()).setPermitMotor(query.value(3).toInt())
				.setPermitTaxi(query.value(4).toInt()).setPermitTruck(query.value(5).toInt())
				.setPermitBus(query.value(6).toInt());
			forbidList << tmpForbid;
		}
	}
	db.commit();
	db.close();
	return forbidList;
}

void DB::fetchDataFromNodeVolumeFiles(QSqlQuery & query)
{
	if (!mFileDir->exists(sNodeCarVolumeFileName))
		throw PathNotExistsException(sNodeCarVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeNonMotorVolumeFileName))
		throw PathNotExistsException(sNodeNonMotorVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeMotorVolumeFileName))
		throw PathNotExistsException(sNodeMotorVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeMotorbikeVolumeFileName))
		throw PathNotExistsException(sNodeMotorbikeVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeTaxiVolumeFileName))
		throw PathNotExistsException(sNodeTaxiVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeTruckVolumeFileName))
		throw PathNotExistsException(sNodeTruckVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sNodeBusVolumeFileName))
		throw PathNotExistsException(sNodeBusVolumeFileName + "do not exist!");
	QFile fileMotor(mFileDir->absoluteFilePath(sNodeMotorVolumeFileName));
	QFile fileNonMotor(mFileDir->absoluteFilePath(sNodeNonMotorVolumeFileName));
	QFile fileMotorbike(mFileDir->absoluteFilePath(sNodeMotorbikeVolumeFileName));
	QFile fileCar(mFileDir->absoluteFilePath(sNodeCarVolumeFileName));
	QFile fileBus(mFileDir->absoluteFilePath(sNodeBusVolumeFileName));
	QFile fileTruck(mFileDir->absoluteFilePath(sNodeTruckVolumeFileName));
	QFile fileTaxi(mFileDir->absoluteFilePath(sNodeTaxiVolumeFileName));
	if(!fileMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeMotorVolumeFileName + " open failed!");
	if(!fileNonMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeNonMotorVolumeFileName + " open failed!");
	if(!fileMotorbike.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeMotorbikeVolumeFileName + " open failed!");
	if(!fileCar.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeCarVolumeFileName + " open failed!");
	if(!fileBus.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeBusVolumeFileName + " open failed!");
	if(!fileTruck.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeTruckVolumeFileName + " open failed!");
	if(!fileTaxi.open( QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sNodeTaxiVolumeFileName + " open failed!");
	QTextStream streamMotor(&fileMotor);
	QTextStream streamNonMotor(&fileNonMotor);
	QTextStream streamMotorbike(&fileMotorbike);
	QTextStream streamCar(&fileCar);
	QTextStream streamBus(&fileBus);
	QTextStream streamTruck(&fileTruck);
	QTextStream streamTaxi(&fileTaxi);
	qreal motorV, nonMotorV, motorbikeV, carV, busV, truckV, taxiV;
	const int NUM_ONCE = 500;
	int num = 1;
	QString sql = "insert into "+sNodeVolumeTableName+" (node_id,motor,non_motor,car,bus,motorbike,truck,taxi) "
		+"values(?,?,?,?,?,?,?,?);";
	while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && !streamMotorbike.atEnd()
		&& !streamCar.atEnd() && !streamBus.atEnd() && !streamTruck.atEnd() && !streamTaxi.atEnd() )
	{
		int i=0;
		QVariantList node_ids,motors, nonMotors, motorbikes, cars, buses, trucks, taxis;
		query.prepare(sql);
		while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && !streamMotorbike.atEnd() 
			&& !streamCar.atEnd() && !streamBus.atEnd() && !streamTaxi.atEnd() && !streamTruck.atEnd()
			&& i < NUM_ONCE)
		{
			streamMotor >> motorV; 
			streamNonMotor >> nonMotorV; 
			streamMotorbike >> motorbikeV;
			streamCar >> carV; 
			streamBus >> busV;
			streamTruck >> truckV; 
			streamTaxi >> taxiV; 
			if (streamMotor.status() || streamNonMotor.status() || streamMotorbike.status() || streamCar.status()
				|| streamBus.status() || streamTruck.status() || streamTaxi.status() )
				break;
			else{
				node_ids << num;
				motors << motorV;
				nonMotors << nonMotorV;
				motorbikes << motorbikeV;
				cars << carV; 
				buses << busV;
				trucks << truckV;
				taxis << taxiV;
			}
			i++; num++;
		}
		query.bindValue(0, node_ids);
		query.bindValue(1, motors);
		query.bindValue(2, nonMotors);
		query.bindValue(3, cars);
		query.bindValue(4, buses);
		query.bindValue(5, motorbikes);
		query.bindValue(6, trucks);
		query.bindValue(7, taxis);
		if (!query.execBatch())
		{
			throw CommonException("insert "+sNodeVolumeTableName+" failed");
		}

	}

}

void DB::createNodeVolumeTable(QSqlQuery & query)
{
	query.exec(sSqlCreateNodeVolumeTable);
}

void DB::createRoadVolumeTable(QSqlQuery & query)
{
	query.exec(sSqlCreateRoadVolumeTable);
}

void DB::setCreateDbName(QString name)
{
	mCreateDbName = name;
}

void DB::setSelectedDbName(QString name)
{
	mSelectedDbName = name;
}

void DB::fetchDataFromRoadVolumeFiles(QSqlQuery & query)
{
	if (!mFileDir->exists(sRoadCarVolumeFileName))
		throw PathNotExistsException(sNodeCarVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadNonMotorVolumeFileName))
		throw PathNotExistsException(sRoadNonMotorVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadMotorVolumeFileName))
		throw PathNotExistsException(sRoadMotorVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadMotorbikeVolumeFileName))
		throw PathNotExistsException(sRoadMotorbikeVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadTaxiVolumeFileName))
		throw PathNotExistsException(sRoadTaxiVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadTruckVolumeFileName))
		throw PathNotExistsException(sRoadTruckVolumeFileName + "do not exist!");
	if (!mFileDir->exists(sRoadBusVolumeFileName))
		throw PathNotExistsException(sRoadBusVolumeFileName + "do not exist!");
	QFile fileMotor(mFileDir->absoluteFilePath(sRoadMotorVolumeFileName));
	QFile fileNonMotor(mFileDir->absoluteFilePath(sRoadNonMotorVolumeFileName));
	QFile fileMotorbike(mFileDir->absoluteFilePath(sRoadMotorbikeVolumeFileName));
	QFile fileCar(mFileDir->absoluteFilePath(sRoadCarVolumeFileName));
	QFile fileBus(mFileDir->absoluteFilePath(sRoadBusVolumeFileName));
	QFile fileTruck(mFileDir->absoluteFilePath(sRoadTruckVolumeFileName));
	QFile fileTaxi(mFileDir->absoluteFilePath(sRoadTaxiVolumeFileName));
	if(!fileMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadMotorVolumeFileName + " open failed!");
	if(!fileNonMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadNonMotorVolumeFileName + " open failed!");
	if(!fileMotorbike.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadMotorbikeVolumeFileName + " open failed!");
	if(!fileCar.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadCarVolumeFileName + " open failed!");
	if(!fileBus.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadBusVolumeFileName + " open failed!");
	if(!fileTruck.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadTruckVolumeFileName + " open failed!");
	if(!fileTaxi.open( QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException( sRoadTaxiVolumeFileName + " open failed!");
	QTextStream streamMotor(&fileMotor);
	QTextStream streamNonMotor(&fileNonMotor);
	QTextStream streamMotorbike(&fileMotorbike);
	QTextStream streamCar(&fileCar);
	QTextStream streamBus(&fileBus);
	QTextStream streamTruck(&fileTruck);
	QTextStream streamTaxi(&fileTaxi);
	qreal motorV, nonMotorV, motorbikeV, carV, busV, truckV, taxiV;
	const int NUM_ONCE = 500;
	int num = 1;
	QString sql = "insert into "+sRoadVolumeTableName+" (road_id,motor,non_motor,car,bus,motorbike,truck,taxi) "
		+"values(?,?,?,?,?,?,?,?);";
	while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && !streamMotorbike.atEnd()
		&& !streamCar.atEnd() && !streamBus.atEnd() && !streamTruck.atEnd() && !streamTaxi.atEnd() )
	{
		int i=0;
		QVariantList road_ids,motors, nonMotors, motorbikes, cars, buses, trucks, taxis;
		query.prepare(sql);
		while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && !streamMotorbike.atEnd() 
			&& !streamCar.atEnd() && !streamBus.atEnd() && !streamTaxi.atEnd() && !streamTruck.atEnd()
			&& i < NUM_ONCE)
		{
			
			streamMotor >> motorV; 
			streamNonMotor >> nonMotorV; 
			streamMotorbike >> motorbikeV; 
			streamCar >> carV; 
			streamBus >> busV; 
			streamTruck >> truckV; 
			streamTaxi >> taxiV; 
			if (streamMotor.status() || streamNonMotor.status() || streamMotorbike.status() || streamCar.status()
				|| streamBus.status() || streamTruck.status() || streamTaxi.status() )
				break;
			else{
				road_ids << num;
				motors << motorV;
				nonMotors << nonMotorV;
				motorbikes << motorbikeV;
				cars << carV; 
				buses << busV;
				trucks << truckV;
				taxis << taxiV;
			}

			i++; num++;
		}
		query.bindValue(0, road_ids);
		query.bindValue(1, motors);
		query.bindValue(2, nonMotors);
		query.bindValue(3, cars);
		query.bindValue(4, buses);
		query.bindValue(5, motorbikes);
		query.bindValue(6, trucks);
		query.bindValue(7, taxis);
		if (!query.execBatch())
		{
			QString str = query.lastError().text();
			throw CommonException("insert "+sRoadVolumeTableName+" failed; "+str);
		}

	}
}

QList<TrafficVolume*> DB::loadNodeTrafficVolume()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	QSqlQuery query(db);
	QString sql = "select node_id,motor,non_motor,car,bus,motorbike,truck,taxi from "+sNodeVolumeTableName;
	QList<TrafficVolume*> volumeList;
	TrafficVolume* tmpVolume;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpVolume = new TrafficVolume;
			tmpVolume->setId(query.value(0).toInt()).setMotorVolume(query.value(1).toReal())
				.setNonMotorVolume(query.value(2).toReal()).setCarVolume(query.value(3).toReal())
				.setBusVolume(query.value(4).toReal()).setMotorbikeVolume(query.value(5).toReal())
				.setTruckVolume(query.value(6).toReal()).setTaxiVolume(query.value(7).toReal());
			volumeList << tmpVolume;
		}

	}
	db.close();
	return volumeList;
}

QList<TrafficVolume*> DB::loadRoadTrafficVolume()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	QSqlQuery query(db);
	QString sql = "select road_id,motor,non_motor,car,bus,motorbike,truck,taxi from "+sRoadVolumeTableName;
	QList<TrafficVolume*> volumeList;
	TrafficVolume* tmpVolume;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpVolume = new TrafficVolume;
			tmpVolume->setId(query.value(0).toInt()).setMotorVolume(query.value(1).toReal())
				.setNonMotorVolume(query.value(2).toReal()).setCarVolume(query.value(3).toReal())
				.setBusVolume(query.value(4).toReal()).setMotorbikeVolume(query.value(5).toReal())
				.setTruckVolume(query.value(6).toReal()).setTaxiVolume(query.value(7).toReal());
			volumeList << tmpVolume;
		}

	}
	db.close();
	return volumeList;
}

void DB::createNodeCapabilityTable(QSqlQuery & query)
{
	query.exec(sSqlCreateNodeCapabilityTable);
}

void DB::createRoadCapabilityTable(QSqlQuery & query)
{
	query.exec(sSqlCreateRoadCapabilityTable);
}

void DB::createSpeedTable(QSqlQuery & query)
{
	query.exec(sSqlCreateSpeedTable);
}

void DB::fetchDataFromNodeCapabilityFile(QSqlQuery & query)
{
	if(!mFileDir->exists(sNodeMotorCapabilityFileName))
		throw PathNotExistsException(sNodeMotorCapabilityFileName+" does not exist!");
	if(!mFileDir->exists(sNodeNonMotorCapabilityFileName))
		throw PathNotExistsException(sNodeNonMotorCapabilityFileName+" does not exist!");
	QFile fileMotor(mFileDir->absoluteFilePath(sNodeMotorCapabilityFileName));
	QFile fileNonMotor(mFileDir->absoluteFilePath(sNodeNonMotorCapabilityFileName));
	if(!fileMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException("open "+sNodeMotorCapabilityFileName+" failed!");
	if(!fileNonMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException("open "+sNodeNonMotorCapabilityFileName+" failed!");
	QTextStream streamMotor(&fileMotor);
	QTextStream streamNonMotor(&fileNonMotor);
	qreal motorCapability, nonMotorCapability;
	const int NUM_ONCE=500;
	int num=1;
	QString sql = "insert into "+sNodeCapabilityTableName+" (node_id,motor,non_motor) "
		+" values (?,?,?);";
	query.prepare(sql);
	while (!streamMotor.atEnd() && !streamNonMotor.atEnd())
	{
		QVariantList node_ids,motors, nonMotors;
		int i=0;
		while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && i<NUM_ONCE)
		{
			streamMotor >> motorCapability;
			streamNonMotor >> nonMotorCapability;
			if(streamMotor.status() || streamNonMotor.status())
				break;
			node_ids << num;
			motors << motorCapability;
			nonMotors << nonMotorCapability;
			++i; ++num;
		}
		query.bindValue(0, node_ids);
		query.bindValue(1, motors);
		query.bindValue(2, nonMotors);
		if(!query.execBatch()){
			QString str = query.lastError().text();
			throw CommonException(str);
		}

	}

}

void DB::fetchDataFromRoadCapabilityFile(QSqlQuery & query)
{
	if(!mFileDir->exists(sRoadMotorCapabilityFileName))
		throw PathNotExistsException(sRoadMotorCapabilityFileName+" does not exist!");
	if(!mFileDir->exists(sRoadNonMotorCapabilityFileName))
		throw PathNotExistsException(sRoadNonMotorCapabilityFileName+" does not exist!");
	QFile fileMotor(mFileDir->absoluteFilePath(sRoadMotorCapabilityFileName));
	QFile fileNonMotor(mFileDir->absoluteFilePath(sRoadNonMotorCapabilityFileName));
	if(!fileMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException("open "+sRoadMotorCapabilityFileName+" failed!");
	if(!fileNonMotor.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException("open "+sRoadNonMotorCapabilityFileName+" failed!");
	QTextStream streamMotor(&fileMotor);
	QTextStream streamNonMotor(&fileNonMotor);
	qreal motorCapability, nonMotorCapability;
	const int NUM_ONCE=500;
	int num=1;
	QString sql = "insert into "+sRoadCapabilityTableName+" (road_id,motor,non_motor) "
		+" values (?,?,?);";
	query.prepare(sql);
	while (!streamMotor.atEnd() && !streamNonMotor.atEnd())
	{
		QVariantList node_ids,motors, nonMotors;
		int i=0;
		while (!streamMotor.atEnd() && !streamNonMotor.atEnd() && i<NUM_ONCE)
		{
			streamMotor >> motorCapability;
			streamNonMotor >> nonMotorCapability;
			if(streamMotor.status() || streamNonMotor.status())
				break;
			node_ids << num;
			motors << motorCapability;
			nonMotors << nonMotorCapability;
			++i; ++num;
		}
		query.bindValue(0, node_ids);
		query.bindValue(1, motors);
		query.bindValue(2, nonMotors);
		if(!query.execBatch()){
			QString str = query.lastError().text();
			throw CommonException(str);
		}

	}
}

void DB::fetchDataFromSpeedFile(QSqlQuery & query)
{
	if(!mFileDir->exists(sSpeedFileName))
		throw PathNotExistsException(sSpeedFileName+" does not exist!");
	QFile fileSpeed(mFileDir->absoluteFilePath(sSpeedFileName));
	if(!fileSpeed.open(QIODevice::ReadOnly | QIODevice::Text))
		throw CommonException("open "+sSpeedFileName+" failed!");
	QTextStream streamSpeed(&fileSpeed);
	qreal speed;
	const int NUM_ONCE=500;
	int num=1;
	QString sql = "insert into "+sSpeedTableName+" (road_id,speed) "
		+" values (?,?);";
	query.prepare(sql);
	while (!streamSpeed.atEnd())
	{
		QVariantList road_ids,speeds;
		int i=0;
		while (!streamSpeed.atEnd() && i<NUM_ONCE)
		{
			streamSpeed >> speed;
			if(streamSpeed.status())
				break;
			road_ids << num;
			speeds << speed;
			++i; ++num;
		}
		query.bindValue(0, road_ids);
		query.bindValue(1, speeds);
		if(!query.execBatch()){
			QString str = query.lastError().text();
			throw CommonException(str);
		}

	}
}

QList<Capability*> DB::loadNodeCapability()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	QSqlQuery query(db);
	QString sql = "select node_id,motor,non_motor from "+sNodeCapabilityTableName;
	QList<Capability*> capabilityList;
	Capability* tmpCapability;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpCapability = new Capability;
			tmpCapability->setId(query.value(0).toInt()).setMotorCapability(query.value(1).toReal())
				.setNonMotorCapability(query.value(2).toReal());
			capabilityList << tmpCapability;
		}

	}
	db.close();
	return capabilityList;
}

QList<Capability*> DB::loadRoadCapability()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	QSqlQuery query(db);
	QString sql = "select road_id,motor,non_motor from "+sRoadCapabilityTableName;
	QList<Capability*> capabilityList;
	Capability* tmpCapability;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpCapability = new Capability;
			tmpCapability->setId(query.value(0).toInt()).setMotorCapability(query.value(1).toReal())
				.setNonMotorCapability(query.value(2).toReal());
			capabilityList << tmpCapability;
		}

	}
	db.close();
	return capabilityList;
}

QList<Speed*> DB::loadSpeed()
{
	QSqlDatabase db = QSqlDatabase::addDatabase(sDbType);
	db.setDatabaseName(mSelectedDbName);
	db.open();
	QSqlQuery query(db);
	QString sql = "select road_id,speed from "+sSpeedTableName;
	QList<Speed*> speedList;
	Speed* tmpSpeed;
	if (query.exec(sql))
	{
		while (query.next())
		{
			tmpSpeed = new Speed;
			tmpSpeed->setId(query.value(0).toInt()).setSpeed(query.value(1).toReal());
			speedList << tmpSpeed;
		}

	}
	db.close();
	return speedList;
}












