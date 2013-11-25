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

	connect(ui->updateButton, SIGNAL(clicked()), this, SLOT(fillPortList()));
}

DeviseWidget::~DeviseWidget()
{
	delete ui;
}

void DeviseWidget::gloveConnectionChanged(const bool &isConnected, const QString &comment)
{

}

void DeviseWidget::handConnectionChanged(const bool &isConnected, const QString &comment)
{

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
