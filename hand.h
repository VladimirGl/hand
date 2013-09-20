#ifndef HAND_H
#define HAND_H

#include <QObject>
#include <QList>

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

	void startSendingData();
	void stopSendingData();

	bool isDataSending();
	bool isPortSet();

	void moveMotor(int const& num, int const& value);
	QList<int> *currentPosition();

signals:
	void dataIsRead();

protected slots:
	void setStartValues();
	void onReadyRead();

protected:
	void setPortSettings();
	bool hasHeader();

	void getDataFromMotors();

private:
	QByteArray mBytes;

	QList<int> mCurrentPosition;

	QSerialPort *mPort;
};

#endif // HAND_H
