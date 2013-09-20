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

class Hand : public QObject
{
	Q_OBJECT
public:
	Hand();
	~Hand();

	/// Checks COM ports for the connected hand.
	void connectHardwareHand();

	/// Opens port.
	void startSendingData();
	/// Closes port.
	void stopSendingData();

	/// Return true, if the port is open.
	bool isDataSending();
	/// Returns true, if portName is set.
	bool isPortSet();

	/// Sends number of servo and the desired degree to the hardware hand.
	void moveMotor(int const& num, int const& value);
	/// Returns servo degrees.
	QList<int> *currentPosition();

signals:
	/// Sent when the computer reads the correct data from the hand.
	void dataIsRead();

protected slots:
	/// Request to set all servos to the start position.
	void setStartValues();
	/// Checks the received data.
	void onReadyRead();

protected:
	/// Returns true if bytes has a valid header.
	bool hasHeader();
	/// Translates data about servos from bytes to integer numbers.
	void getDataFromMotors();

	void setPortSettings();

private:
	QByteArray mBytes;

	QList<int> mCurrentPosition;

	QSerialPort *mPort;
};

#endif // HAND_H
