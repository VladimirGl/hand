#include "action.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Action w;
	w.show();

	return a.exec();
}
