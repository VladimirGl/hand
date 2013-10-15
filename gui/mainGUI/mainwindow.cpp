#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "../../translator.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	int jg = 6;

	mActionWidget = new ActionWidget;
	mGraphicalWidget = new GraphicalWidget(jg);

	i = 0;

	ui->stackedWidget->addWidget(mActionWidget);
	ui->stackedWidget->addWidget(mGraphicalWidget);

	connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

	connect(mActionWidget, SIGNAL(startLoading(QString)), this, SLOT(startLoading(QString)));
	connect(mActionWidget, SIGNAL(stopLoading()), this, SLOT(stopLoading()));
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::buttonClicked()
{
	i = (i + 1) % 4;

	ui->stackedWidget->setCurrentIndex(i);
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
