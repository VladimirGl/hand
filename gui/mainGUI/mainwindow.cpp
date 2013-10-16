#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "../../translator.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	mActionWidget = new ActionWidget;

	i = 0;

	ui->stackedWidget->addWidget(mActionWidget);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

	connect(mActionWidget, SIGNAL(startLoading(QString)), this, SLOT(startLoading(QString)));
	connect(mActionWidget, SIGNAL(stopLoading()), this, SLOT(stopLoading()));

	connect(mActionWidget, SIGNAL(startSaveing(QString,int)), this, SLOT(startSaveing(QString,int)));
	connect(mActionWidget, SIGNAL(stopSaveing()), this, SLOT(stopSaveing()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::buttonClicked()
{
	ui->stackedWidget->setCurrentIndex(2);
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
