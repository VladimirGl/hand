#ifndef ACTIONLOADER_H
#define ACTIONLOADER_H

#include "actionFileStructure.h"

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

class ActionLoader : public QObject, ActionFileStructure
{
	Q_OBJECT
public:
	ActionLoader(const QString &fileName);

	bool isFileCorrect() const;
	bool isFileEnd() const;

	int freq() const { return mFreq; }

	void startSendingData();
	void stopSendingData();

	QList<int> data();

signals:
	void onReadyRead();

protected:
	void propertiesParse();

	void readFrequency();
	void readNumberOfDOF();

	bool isValueCorrect(const int &val) const;

private:
	QFile mFile;
	QTextStream mStream;

	bool mIsFileCorrect;
	bool mIsFileEnd;

	int mFreq;
	int mNumberOfDOF;
};

#endif // ACTIONLOADER_H
