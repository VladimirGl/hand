#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../translator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mActionWidget = new ActionWidget;
	mCalibratorWidget = new CalibratorWidget;
	mDeviseWidget = new DeviseWidget;

	mCurrWidget = 4;

	ui->stackedWidget->addWidget(mActionWidget);
	ui->stackedWidget->addWidget(mCalibratorWidget);
	ui->stackedWidget->addWidget(mDeviseWidget);
	ui->stackedWidget->setCurrentIndex(mCurrWidget);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));


	actionWidgetConnector();
	calibratorWidgetConnector();
	deviseWidgetConnector();
}

MainWindow::~MainWindow()
{
	delete ui;

	delete mActionWidget;
	delete mCalibratorWidget;
	delete mDeviseWidget;
}

void MainWindow::buttonClicked()
{
	if (mCurrWidget == 2) {
		mCurrWidget = 3;
	} else if (mCurrWidget == 3) {
		mCurrWidget = 4;
	} else if (mCurrWidget == 4) {
		mCurrWidget = 2;
	}

	ui->stackedWidget->setCurrentIndex(mCurrWidget);
}

void MainWindow::startLoading(const QString &fileName)
{
	mTranslator->startLoadAction(fileName);

	connect(mTranslator, SIGNAL(loadingStoped()), this, SLOT(stopLoading()));
}

void MainWindow::stopLoading()
{
	disconnect(mTranslator, SIGNAL(loadingStoped()), this, SLOT(stopLoading()));

	mActionWidget->dataEnd();
	mTranslator->stopLoadAction();
}

void MainWindow::startSaveing(const QString &fileName, const int &freq)
{
	mTranslator->startSaveAction(fileName, freq);
}

void MainWindow::stopSaveing()
{
	mActionWidget->saveingEnd();
	mTranslator->stopSaveAction();
}

void MainWindow::startCalibrate()
{
	mTranslator->startCalibrate();
}

void MainWindow::stopCalibrate()
{
	mTranslator->stopCalibrate();
}

void MainWindow::connectGlove(const QString &portName)
{
	mTranslator->connectGlove(portName);
}

void MainWindow::connectHand(const QString &portName)
{
	mTranslator->connectHand(portName);
}

void MainWindow::updateDeviseInfo()
{
	mDeviseWidget->gloveConnection(mTranslator->isGloveConnected());
	mDeviseWidget->handConnection(mTranslator->isHandConnected());
}

void MainWindow::actionWidgetConnector()
{
	connect(mActionWidget, SIGNAL(startLoading(QString)), this, SLOT(startLoading(QString)));
	connect(mActionWidget, SIGNAL(stopLoading()), this, SLOT(stopLoading()));

	connect(mActionWidget, SIGNAL(startSaveing(QString,int)), this, SLOT(startSaveing(QString,int)));
	connect(mActionWidget, SIGNAL(stopSaveing()), this, SLOT(stopSaveing()));
}

void MainWindow::calibratorWidgetConnector()
{
	connect(mCalibratorWidget, SIGNAL(startCalibrate()), this, SLOT(startCalibrate()));
	connect(mCalibratorWidget, SIGNAL(stopCalibrate()), this, SLOT(stopCalibrate()));
}

void MainWindow::deviseWidgetConnector()
{
	connect(mDeviseWidget, SIGNAL(updateDeviseInfo()), this, SLOT(updateDeviseInfo()));

	connect(mDeviseWidget, SIGNAL(tryGloveConnect(QString)), this, SLOT(connectGlove(QString)));
	connect(mDeviseWidget, SIGNAL(tryHandConnect(QString)), this, SLOT(connectHand(QString)));
}
