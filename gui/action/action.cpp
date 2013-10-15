#include "action.h"
#include "ui_action.h"

#include <QDir>
#include <QStringList>

#include <QDebug>

#include "../../fileActionPerformer.h"

Action::Action(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Action)
{
	ui->setupUi(this);

	QDir dir("/home/rayman/Downloads/anakinHand/gui/action/actionFiles");

	QStringList filter;
	filter.append("*.act");
	QStringList list = dir.entryList(filter, QDir::Files);

	mActionPerformer = new FileActionPerformer;

	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(print()));
	connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopData()));

	ui->comboBox->addItems(list);
}

Action::~Action()
{
	delete ui;
}

void Action::print()
{
	qDebug() << ui->comboBox->currentText();

	mActionPerformer->startLoad("/home/rayman/Downloads/anakinHand/gui/action/actionFiles/"
			+ ui->comboBox->currentText());

	qDebug() << mActionPerformer->isLoaded();
	qDebug() << mActionPerformer->isFileCorrect();

	if (mActionPerformer->isFileCorrect()) {
		ui->checkBox->setChecked(true);
		connect(mActionPerformer, SIGNAL(onReadyLoad()), this, SLOT(loadData()));
	}
}

void Action::loadData()
{
	if (mActionPerformer->isFileEnd() || !mActionPerformer->isFileCorrect()) {
		disconnect(mActionPerformer, SIGNAL(onReadyLoad()), this, SLOT(loadData()));
		stopData();
		return;
	}

	qDebug() << "start:";
	qDebug() << mActionPerformer->data();
	qDebug() << "stop";
}

void Action::stopData()
{
	ui->checkBox->setChecked(false);
	disconnect(mActionPerformer, SIGNAL(onReadyLoad()), this, SLOT(loadData()));
	mActionPerformer->stopLoad();
}
