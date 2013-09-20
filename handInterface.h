#ifndef HANDINTERFACE_H
#define HANDINTERFACE_H

#include <QObject>
#include <QList>

/**
* @file handInterface.h
*
* Implementation of GloveInterface class.
* All interaction with the hand comes through this class.
*/

class Hand;

class HandInterface : public QObject
{
	Q_OBJECT
public:
	HandInterface();
	~HandInterface();

	/// Trying to connect mHand with a real glove.
	void setHardwareHand();
	/// Returns true if mHand serial port set.
	bool isHardwareHandSet();

	/// Calls the appropriate method of the Hand class.
	void startSendingDatas();
	/// Calls the appropriate method of the Hand class.
	void stopSendingDatas();

	/// Request hardware hand to set servo number num to value.
	void moveMotor(int const& num, int const& value);
	/// Returns last datas from the servos.
	QList<int> *motorsDatas();

signals:
	/// Re emits the signal of the glove.
	void dataIsRead();

private:
	Hand *mHand;
};

#endif // HANDINTERFACE_H
