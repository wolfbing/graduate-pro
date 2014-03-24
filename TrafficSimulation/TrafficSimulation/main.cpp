#include "trafficsimulation.h"
#include <QtWidgets/QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	// 以下部分解决中文乱码   
	//QTextCodec::setCodecForLocale(QTextCodec::codecForName("utf8"));    
	// 以上部分解决中文乱码

	TrafficSimulation w;
	w.show();
	return a.exec();
}
