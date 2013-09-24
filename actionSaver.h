#ifndef ACTIONSAVER_H
#define ACTIONSAVER_H

#include "actionFileStructure.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

class ActionSaver : public QObject, ActionFileStructure
{
	Q_OBJECT
public:
	ActionSaver(const int &freq
			, const int &numOfDOF
			, const QString &fileName);

	void writeData(const QList<int> &data);
	void stopRecord();

signals:
	void onReadyWrite();

protected:
	void writePropertiesData();

private:
	QFile mFile;
	QTextStream mStream;

	int mFreq;
	int mNumberOfDOF;
};

#endif // ACTIONSAVER_H
