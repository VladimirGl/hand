#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../action/actionWidget.h"
#include "../../fileActionPerformer.h"

namespace Ui {
class MainWindow;
}

class Translator;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);

	void setTranslator(Translator *translator) { mTranslator = translator; }
	~MainWindow();

protected slots:
	void buttonClicked();

protected slots:
	void startLoading(const QString &fileName);
	void stopLoading();

	void startSaveing(const QString &fileName, const int &freq);
	void stopSaveing();

private:
	Ui::MainWindow *ui;

	Translator *mTranslator;

	int i;

	ActionWidget *mActionWidget;
};

#endif // MAINWINDOW_H
