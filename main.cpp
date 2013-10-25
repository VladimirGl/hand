#include "gui/mainwindow.h"
#include <QApplication>

#include "translator.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	Translator *translator = new Translator;

	translator->setConnectionType(noConnection);
//	translator->connectHand();
	translator->connectGlove();

	w.setTranslator(translator);
	
	return a.exec();
}
