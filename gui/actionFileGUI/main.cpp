#include "actionFileWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ActionFileWidget w;
	w.show();

	return a.exec();
}
