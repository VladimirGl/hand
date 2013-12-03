#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "actionWidget.h"
#include "calibratorWidget.h"
#include "deviseWidget.h"
#include "graphicalWidget.h"

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

	void startSaving(const QString &fileName, const int &freq);
	void stopSaving();

	void startCalibrate();
	void stopCalibrate();

	void connectGlove(const QString& portName);
	void connectHand(const QString& portName);
	void updateDeviseInfo();

	void updater();

private:
	enum Widgets {
		action = 2,
		calibrator,
		devise,
		graphical
	};

	void actionWidgetConnector();
	void calibratorWidgetConnector();
	void deviseWidgetConnector();

	Ui::MainWindow *ui;

	Translator *mTranslator;

	int mCurrWidget;

	ActionWidget *mActionWidget;
	CalibratorWidget *mCalibratorWidget;
	DeviseWidget *mDeviseWidget;
	GraphicalWidget *mGraphicalWidget;
};

#endif // MAINWINDOW_H
