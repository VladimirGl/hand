#ifndef ACTION_H
#define ACTION_H

#include <QList>

class QTextStream;
class QString;

class Action
{
public:
	Action();
	Action(QString const& fileName);

	void loadAction(QString const& fileName);
	void startPlayingAction();
	QString data() const;

	void startSaveAction(QString const& fileName
			, int const& newFrequency
			, int const& numberOfDOF);
	void loadOneMovement(QList<int> const& list);
	void stopSaveAction();

	int frequency();
	int numberOfDegreesOfFreedoms();

private:
	bool isNewAction;

	int mFrequency;
	int mNumberOfDegreesOfFreedoms;

	QTextStream mActionTextStream;
};

#endif // ACTION_H
