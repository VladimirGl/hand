#ifndef ACTIONSAVER_H
#define ACTIONSAVER_H

#include "actionFileStructure.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

/**
* @file actionSaver.h
*
* Implementation of ActionSaver class.
* Used to save action to the file.
*/

class ActionSaver : public QObject, ActionFileStructure
{
	Q_OBJECT
public:
	ActionSaver(const int &freq
			, const int &numOfDOF
			, const QString &fileName);

	/// Write one motion to the file.
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
