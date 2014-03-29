
#include <QtWidgets/QApplication>
#include <QtWidgets>
#include <QGLWidget>

#include <QtDebug>

#include "winofgraphicsview.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	WinOfGraphicsView w;

	w.show();

	return a.exec();
}
