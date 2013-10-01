#ifndef USERFILELOADER_H
#define USERFILELOADER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "userFileStructure.h"

class UserFileLoader : public UserFileStructure
{
public:
	UserFileLoader(const QString &fileName);

	bool isFileCorrect() const { return mIsFileCorrect; }
	bool isFileEnd() const { return mIsFileEnd; }

	bool isDOFRead() const { return mIsDOFData; }
	bool isConformityRead() const { return mIsConformityData; }

	QList<int> DOFList();

	QList<int> conformityList();

protected:
	void beginParse();

	void readDOF();
	void readConformity();

	bool isDOFcorrect(const int &min, const int &max);

private:
	bool mIsDOFData;
	bool mIsConformityData;

	bool mIsFileCorrect;
	bool mIsFileEnd;

	QFile mFile;
	QTextStream mStream;
};

#endif // USERFILELOADER_H
