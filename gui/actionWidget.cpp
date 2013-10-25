#include "actionWidget.h"
#include "ui_actionWidget.h"

#include <QDir>
#include <QStringList>

ActionWidget::ActionWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Action)
{
	ui->setupUi(this);

	QString path = PRO_FILE_PWD;

	QDir dir(path + "/actionFiles");

	QStringList filter;
	filter.append("*.act");
	QStringList list = dir.entryList(filter, QDir::Files);

	connect(ui->startLoadButton, SIGNAL(clicked()), this, SLOT(startLoad()));
	connect(ui->stopLoadButton, SIGNAL(clicked()), this, SLOT(stopLoad()));

	connect(ui->startSaveButton, SIGNAL(clicked()), this, SLOT(startSave()));
	connect(ui->stopSaveButton, SIGNAL(clicked()), this, SLOT(stopSave()));

	ui->comboBox->addItems(list);
}

ActionWidget::~ActionWidget()
{
	delete ui;
}

void ActionWidget::dataEnd()
{
	ui->isLoadedCheckBox->setChecked(false);
}

void ActionWidget::saveingEnd()
{
	ui->isSavedCheckBox->setChecked(false);
}

void ActionWidget::startLoad()
{
	QString fileName = "/home/rayman/Downloads/anakinHand/gui/action/actionFiles/"
			+ ui->comboBox->currentText();

	ui->isLoadedCheckBox->setChecked(true);

	emit startLoading(fileName);
}

void ActionWidget::stopLoad()
{
	ui->isLoadedCheckBox->setChecked(false);

	emit stopLoading();
}

void ActionWidget::startSave()
{
	QString fileName = "/home/rayman/Downloads/anakinHand/gui/ActionWidget/ActionWidgetFiles/"
			+ ui->comboBox->currentText();

	ui->isSavedCheckBox->setChecked(true);

	int freq = ui->freqLineEdit->text().toInt();

	emit startSaveing(fileName, freq);
}

void ActionWidget::stopSave()
{
	ui->isSavedCheckBox->setChecked(false);

	emit stopSaveing();
}
