#ifndef GLOVEINTERFACE_H
#define GLOVEINTERFACE_H

#include <QObject>
#include <QList>

/**
* @file gloveInterface.h
*
* Implementation of GloveInterface class.
* All interaction with the glove comes through this class.
*/

class Glove;

class GloveInterface : public QObject
{
	Q_OBJECT
public:
	GloveInterface();
	~GloveInterface();

	/// Trying to connect mGlove with a real glove.
	void setHardwareGlove(const QString& portName);
	/// Returns true if mGlove serial port set.
	bool isHardwareGloveSet();
	/// Return true, if the port is open.
	bool isDataSending() const;

	/// Calls the appropriate method of the Glove class.
	void startSendingDatas();
	/// Calls the appropriate method of the Glove class.
	void stopSendingDatas();

	QList<int> gloveDatas();

signals:
	/// Re emits the signal of the glove.
	void dataIsRead();

private:
	Glove *mGlove;

	bool mIsConnected;
};

#endif // GLOVEINTERFACE_H
