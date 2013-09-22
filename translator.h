#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QObject>
#include <QList>

class ActionPerfomer;
class GloveInterface;
class HandInterface;
class User;

enum ConnectionType {
	noConnection = 0,
	gloveToHand = 1,
	actionToHand = 2
};

class Translator :  public QObject
{
public:
	Translator();
	~Translator();

	bool connectGlove();
	bool connectHand();

	void startConnection();

	QList<int> *sensorData() { return &mSensorDatas; }
	QList<int> *convertedData() { return &mConvertedDatas; }

	void setConnectionType(ConnectionType const& type) { mConnectionType = type; }
	ConnectionType connectionType() const { return mConnectionType; }

protected slots:
	void convertData();
	void sendDataToHand();

protected:
	void saveConvertedData(QList<int> const& data);
	void saveSensorsData(QList<int> const& data);

	int map(int const& value
			, int const& firstMin, int const& firstMax
			, int const& secondMin, int const& secondMax);

	int map(int const& value
			, int const& min, int const& max);

private:
	ConnectionType mConnectionType;

	QList<int> mConvertedDatas;
	QList<int> mSensorDatas;

	User *mUser;

	ActionPerfomer *mActionsPerfomer;
	GloveInterface *mGloveInterface;
	HandInterface *mHandInterface;
};

#endif // TRANSLATOR_H
