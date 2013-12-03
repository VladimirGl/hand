#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "../translator.h"
#include "../consts.h"

#include <QTimer>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(updater()));
	timer->start(1000 / 33);

	mActionWidget = new ActionWidget;
	mCalibratorWidget = new CalibratorWidget(GloveConsts::numberOfSensors);
	mDeviseWidget = new DeviseWidget;
	mGraphicalWidget = new GraphicalWidget(GloveConsts::numberOfSensors);

	mCurrWidget = devise;

	ui->stackedWidget->addWidget(mActionWidget);
	ui->stackedWidget->addWidget(mCalibratorWidget);
	ui->stackedWidget->addWidget(mDeviseWidget);
	ui->stackedWidget->addWidget(mGraphicalWidget);
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
	switch (mCurrWidget)
	{
	case action :
	{
		mCurrWidget = calibrator;
		break;
	}
	case calibrator :
	{
		mCurrWidget = graphical;
		break;
	}
	case graphical :
	{
		mCurrWidget = devise;
		break;
	}
	case devise :
	{
		mCurrWidget = action;
		break;
	}
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

void MainWindow::startSaving(const QString &fileName, const int &freq)
{
	mTranslator->startSaveAction(fileName, freq);
}

void MainWindow::stopSaving()
{
	mActionWidget->savingEnd();
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

void MainWindow::updater()
{
	switch (mCurrWidget)
	{
	case action :
	{
		break;
	}
	case calibrator :
	{
		if (!mTranslator->isCalibrateing()) {
			break;
		}

		mCalibratorWidget->setData(mTranslator->sensorsMin(), mTranslator->sensorsMax(), mTranslator->sensorData());
		break;
	}
	case devise :
	{
		break;
	}
	}
}

void MainWindow::actionWidgetConnector()
{
	connect(mActionWidget, SIGNAL(startLoading(QString)), this, SLOT(startLoading(QString)));
	connect(mActionWidget, SIGNAL(stopLoading()), this, SLOT(stopLoading()));

	connect(mActionWidget, SIGNAL(startSaving(QString,int)), this, SLOT(startSaving(QString,int)));
	connect(mActionWidget, SIGNAL(stopSaving()), this, SLOT(stopSaving()));
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
