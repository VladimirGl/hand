#include "deviseWidget.h"
#include "ui_deviseWidget.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QList>

DeviseWidget::DeviseWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::DeviseWidget)
{
	ui->setupUi(this);

	fillPortList();

	ui->isGloveConnectedBox->setCheckable(false);
	ui->isHandConnectedBox->setCheckable(false);

	connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(fillPortList()));
	connect(ui->updateButton, SIGNAL(clicked()), this, SIGNAL(updateDeviseInfo()));

	connect(ui->connectGloveButton, SIGNAL(clicked()), this, SLOT(gloveConnection()));
	connect(ui->connectHandButton, SIGNAL(clicked()), this, SLOT(handConnection()));
}

DeviseWidget::~DeviseWidget()
{
	delete ui;
}

void DeviseWidget::gloveConnection(const bool &isConnected)
{
	ui->isGloveConnectedBox->setChecked(isConnected);
}

void DeviseWidget::handConnection(const bool &isConnected)
{
	ui->isHandConnectedBox->setChecked(isConnected);
}

void DeviseWidget::fillPortList()
{
	QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();

	mPortsList.clear();

	for (int i = 0; i < list.size(); i++) {
		QString name = list.at(i).portName();
		if (name.contains("ttyACM")) {
			mPortsList.append(name);
		}
	}

	ui->availablePortsList->clear();
	ui->availablePortsList->addItems(mPortsList);
}

void DeviseWidget::gloveConnection()
{
	QString currPort = ui->availablePortsList->currentText();

	if (!currPort.isEmpty()) {
		emit tryGloveConnect(currPort);
	}
}

void DeviseWidget::handConnection()
{
	QString currPort = ui->availablePortsList->currentText();

	if (!currPort.isEmpty()) {
		emit tryHandConnect(currPort);
	}
}
