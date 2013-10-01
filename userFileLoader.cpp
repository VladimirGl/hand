#include "userFileLoader.h"

#include <QStringList>

#include "consts.h"

UserFileLoader::UserFileLoader(const QString &fileName) :
	mIsDOFData(false),
	mIsConformityData(false),
	mIsFileCorrect(true),
	mIsFileEnd(false)
{
	mFile.setFileName(fileName);
	mFile.open(QFile::ReadOnly | QFile::Truncate);

	mStream.setDevice(&mFile);

	beginParse();
}

QList<int> UserFileLoader::DOFList()
{
	QStringList strList = mStream.readLine().split(" ");

	QList<int> intList;
	intList.prepend(0);
	intList.prepend(0);

	if (strList.at(0) == UserFileStructure::endWord()) {
		mIsDOFData = false;
		readConformity();
		return intList;
	}

	if (strList.size() != 2) {
		mIsFileCorrect = false;
		return intList;
	}

	intList[0] = strList.at(0).toInt();
	intList[1] = strList.at(1).toInt();

	if (!isDOFcorrect(intList.at(0), intList.at(1))) {
		mIsFileCorrect = false;
	}

	return intList;
}

QList<int> UserFileLoader::conformityList()
{
	QStringList strList = mStream.readLine().split(" ");

	const int size = strList.size();

	QList<int> intList;
	for (int i = 0; i < size; i++) {
		intList.prepend(0);
	}

	if (strList.at(0) == UserFileStructure::endWord()) {
		mIsConformityData = false;
		mIsFileEnd = true;
		return intList;
	}

	for (int i = 0; i < size; i++) {
		intList[i] = strList.at(i).toInt();
	}

	return intList;
}

void UserFileLoader::beginParse()
{
	if (mStream.readLine() != UserFileStructure::header()) {
		mIsFileCorrect = false;
		return;
	}

	readDOF();
}

void UserFileLoader::readDOF()
{
	QString str;
	mStream >> str;

	if (str != UserFileStructure::DOFKeyWord()) {
		mIsFileCorrect = false;
		return;
	}

	mStream.readLine();

	mStream >> str;

	if (str != UserFileStructure::startWord()) {
		mIsFileCorrect = false;
		return;
	}

	mStream.readLine();
}

void UserFileLoader::readConformity()
{
	QString str;
	mStream >> str;

	if (str != UserFileStructure::endWord()) {
		mIsFileCorrect = false;
		return;
	}

	mStream.readLine();

	mStream >> str;

	if (str != UserFileStructure::conformityKeyWord()) {
		mIsFileCorrect = false;
		return;
	}

	mStream.readLine();

	mStream >> str;

	if (str != UserFileStructure::startWord()) {
		mIsFileCorrect = false;
		return;
	}

	mStream.readLine();
}

bool UserFileLoader::isDOFcorrect(const int &min, const int &max)
{
	if (min >= max) {
		return false;
	}

	if (min < SensorsConsts::min) {
		return false;
	}

	if (max > SensorsConsts::max) {
		return false;
	}

	return true;
}
