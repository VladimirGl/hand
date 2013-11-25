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
	void connectHardwareGlove(const QString &portName);

	/// Opens port.
	void startSendingData();
	/// Closes port.
	void stopSendingData();

	/// Return true, if the port is open.
	bool isDataSending() const;
	/// Returns true, if portName is set.
	bool isPortSet() const;

	/// Returns the latest data from the sensors.
	QList<int> data() const;

signals:
	/// Sent when the computer reads the correct data from the glove.
	void dataIsRead();


	void connectionTryEnd(const bool& isConnected);

protected slots:
	/// Checks the received data.
	void onReadyRead();

	/// Do all you need, if the try of connection failed.
	void connectionTry();

protected:
	/// Returns true if bytes has a valid header.
	bool hasHeader() const;

	/// Returns true if bytes has a valid tail.
	bool hasTail() const;

	/// Translates data about flex sensors from bytes to integer numbers.
	void getDataFromFlexSensors();

	void setPortSettings();

private:
	QByteArray mBytes;

	QList<int> mLastData;

	QSerialPort *mPort;

	bool mIsGloveSet;
	bool mIsConnectionMode;
};

#endif // GLOVE_H
