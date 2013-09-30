#include "mainWindow.h"
#include <QApplication>

#include "translator.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	Translator *translator = new Translator;
	translator->connectGlove();
	translator->connectHand();

	translator->setConnectionType(gloveToHand);

	translator->startConnection();
	
	return a.exec();
}
