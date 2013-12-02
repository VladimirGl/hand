#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <QList>

/**
* @file hand.h
*
* Implementation of Hand class.
* Used to send and read data from the hardware hand through the COM port.
*/

class QSerialPort;
class QByteArray;
class QString;
class QTimer;

class Hand : public QObject
{
	Q_OBJECT
public:
	Hand();
	~Hand();

	/// Try to connect port with name = portName as hand.
	void connectHardwareHand(const QString& portName);

	/// Opens port.
	bool startSendingData();
	/// Closes port.
	void stopSendingData();

	/// Return true, if the port is open.
	bool isDataSending() const;
	/// Returns true, if portName is set.
	bool isPortSet() const;

	/// Sends number of servo and the desired degree to the hardware hand.
	void moveMotor(int const& num, int const& value);

	/// Returns servo degrees.
	QList<int> currentPosition() const;

signals:
	/// Sent when the computer reads the correct data from the hand.
	void dataIsRead();

	/// Sent after trying to connect. isConnected = true, if the devise is correctly connected.
	void connectionTryEnd(const bool& isConnected);

protected slots:
	/// Request to set all servos to the start position.
	void setStartValues();

	/// Checks the received data.
	void onReadyRead();

	/// Do all you need, if the try of connection failed.
	void connectionTry();

	/// Checks if glove is connected.
	void checkIsCanBeConnected();

protected:
	/// Returns true if bytes has a valid header.
	bool hasHeader() const;

	/// Returns true if bytes has a valid tail.
	bool hasTail() const;

	/// Translates data about servos from bytes to integer numbers.
	void getDataFromMotors();

	void setPortSettings();

private:
	QByteArray mBytes;

	QList<int> mCurrentPosition;

	QSerialPort *mPort;

	QTimer *mPortAvailableTimer;

	bool mIsHandSet;
	bool mIsStartSendingData;
	bool mIsConnectionMode;
};

#endif // HAND_H
