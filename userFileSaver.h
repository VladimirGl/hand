#ifndef USERFFILESAVER_H
#define USERFFILESAVER_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QList>

#include "userFileStructure.h"

class UserFileSaver : public UserFileStructure
{
public:
	UserFileSaver(const QString &fileName);

	void writeDOFData(const int &min, const int &max);
	void writeConformityData(const QList<int> &data);

	void stopWriteFile();

protected:
	void startWriteFile();
	void writeConformityHeaders();

private:
	bool mIsConformityDataStart;

	QFile mFile;
	QTextStream mStream;
};

#endif // USERFFILESAVER_H
