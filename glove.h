#ifndef GLOVE_H
#define GLOVE_H

#include <QObject>
#include <QList>

/**
* @file glove.h
*
* Implementation of Glove class.
* Used to get data from the glove with sensors through the COM port.
*/

class QSerialPort;
class QByteArray;
class QString;

class Glove : public QObject
{
	Q_OBJECT
public:
	Glove();
	~Glove();

	/// Checks COM ports for the connected glove.
	void connectHardwareGlove();

	/// Opens port.
	void startSendingData();
	/// Closes port.
	void stopSendingData();

	/// Return true, if the port is open.
	bool isDataSending();
	/// Returns true, if portName is set.
	bool isPortSet();

	/// Returns the latest data from the sensors.
	QList<int> *data();

signals:
	/// Sent when the computer reads the correct data from the glove.
	void dataIsRead();

protected slots:
	/// Checks the received data.
	void onReadyRead();

protected:
	/// Returns true if bytes has a valid header.
	bool hasHeader() const;
	/// Translates data from bytes to integer numbers.
	void getDataFromFlexSensors();

private:
	void setPortSettings();

	QByteArray mBytes;

	QList<int> mLastData;

	QSerialPort *mPort;
};

#endif // GLOVE_H
