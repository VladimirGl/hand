#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QList>

/**
* @file translator.h
*
* Implementation of the class Translator.
* It is the main class of the programm.
* It is connects all the components of the program.
*/

class FileActionPerformer;
class FileUserPerformer;
class GloveInterface;
class HandInterface;
class User;
class GloveCalibrator;

enum ConnectionType {
	noConnection = 0,
	gloveToHand = 1,
	actionToHand = 2,
	calibrate = 3
};

class Translator :  public QObject
{
	Q_OBJECT
public:
	Translator();
	~Translator();

	/// Try to connect hardware glove. Returns true, if the glove is successfully connected.
	bool connectGlove();
	/// Try to connect hardware hand. Returns true, if the glove is successfully connected.
	bool connectHand();

	/// Esteblishes a connection of components, described in the current connection type.
	void startConnection();
	/// Stops all connections.
	void stopConnection();

	/// Returns an list of the last read data.
	QList<int> sensorData() { return mSensorDatas; }
	/// Returns an list of the last converted to hand data.
	QList<int> convertedData() { return mConvertedDatas; }

	/// Stops all connections, and set current connection type = type.
	void setConnectionType(ConnectionType const& type);
	/// Return current connection type.
	ConnectionType connectionType() const { return mConnectionType; }

	/**
	 * Starts loading action from the file.
	 * Sets current connection type = actionToHand.
	 * Start to send data to the hand.
	 */
	void startLoadAction(const QString &fileName);
	/// Stops loading action and set current connection type = noConnection.
	void stopLoadAction();

	/// Starts saveing action to the file. Saves converted to hand data.
	void startSaveAction(const QString &fileName, const int &freq);
	/// Stops saveing action and set current connection type = noConnection.
	void stopSaveAction();

	/// Sets connection type = calibrate and start to calibrate glove.
	void startCalibrate();

public slots:
	void stopCalibrate();

protected slots:
	void convertData();
	void sendDataToCalibrator();

signals:
	/// Emited, when the translator recieves new data from the glove.
	void dataIsRead();
	void loadingStoped();

protected:
	void saveConvertedData(QList<int> const& data);
	void saveSensorsData(QList<int> const& data);

	int map(int const& value
			, int const& firstMin, int const& firstMax
			, int const& secondMin, int const& secondMax);

	int map(int const& value
			, int const& min, int const& max);

	void sendDataToHand();

private:
	ConnectionType mConnectionType;

	QList<int> mConvertedDatas;
	QList<int> mSensorDatas;

	User *mUser;

	FileActionPerformer *mFileActionPerformer;
	FileUserPerformer *mFileUserPerformer;
	GloveCalibrator *mGloveCalibrator;

	GloveInterface *mGloveInterface;
	HandInterface *mHandInterface;
};

#endif // TRANSLATOR_H
