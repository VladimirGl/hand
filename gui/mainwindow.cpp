#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "../translator.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mActionWidget = new ActionWidget;
	mCalibratorWidget = new CalibratorWidget;

	mCurrWidget = 3;

	ui->stackedWidget->addWidget(mActionWidget);
	ui->stackedWidget->addWidget(mCalibratorWidget);
	ui->stackedWidget->setCurrentIndex(mCurrWidget);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));


	actionWidgetConnector();
	connect(mCalibratorWidget, SIGNAL(startCalibrate()), this, SLOT(startCalibrate()));
	connect(mCalibratorWidget, SIGNAL(stopCalibrate()), this, SLOT(stopCalibrate()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::buttonClicked()
{
	if (mCurrWidget == 2) {
		mCurrWidget = 3;
	} else if (mCurrWidget == 3) {
		mCurrWidget =2;
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
