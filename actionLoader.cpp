#include "actionLoader.h"

#include <QStringList>

ActionLoader::ActionLoader(const QString &fileName) :
	mIsFileCorrect(true),
	mIsFileEnd(false)
{
	mFile.setFileName(fileName);
	mFile.open(QFile::ReadOnly | QFile::Truncate);

	mStream.setDevice(&mFile);

	propertiesParse();
}

bool ActionLoader::isFileCorrect() const
{
	return mIsFileCorrect;
}

bool ActionLoader::isFileEnd() const
{
	return mIsFileEnd;
}

QList<int> ActionLoader::data()
{
	QStringList strList = mStream.readLine().split(" ");

	QList<int> intList;
	for (int i = 0; i < mNumberOfDOF; i++) {
		intList.prepend(0);
	}

	if (strList.at(0) == ActionFileStructure::endActionKeyWord()) {
		mIsFileEnd = true;
		return intList;
	}

	if (strList.size() != mNumberOfDOF) {
		mIsFileCorrect = false;
		return intList;
	}

	for (int i = 0; i < mNumberOfDOF; i++) {
		int val = strList.at(i).toInt();

		if (!isValueCorrect(val)) {
			mIsFileCorrect = false;
			return intList;
		}

		intList[i] = val;
	}

	return intList;
}

void ActionLoader::propertiesParse()
{
	if (mStream.readLine() != ActionFileStructure::header()) {
		mIsFileCorrect = false;
		return;
	}

	readFrequency();
	readNumberOfDOF();

	if (mStream.readLine() != ActionFileStructure::startActionKeyWord()) {
		mIsFileCorrect = false;
		return;
	}
}

void ActionLoader::readFrequency()
{
	QString str;
	mStream >> str;

	if (str != ActionFileStructure::freqKeyWord()) {
		mIsFileCorrect = false;
		return;
	}

	int freq = 0;
	mStream >> freq;

	if (freq < FreqLimits::minFreq || freq > FreqLimits::maxFreq) {
		mIsFileCorrect = false;
		return;
	}

	mFreq = freq;

	mStream.readLine();
}

void ActionLoader::readNumberOfDOF()
{
	QString str;
	mStream >> str;

	if (str != ActionFileStructure::DOFKeyWord()) {
		mIsFileCorrect = false;
		return;
	}

	int DOF = 0;
	mStream >> DOF;

	if (DOF < DOFLimits::minDOFs || DOF > DOFLimits::maxDOFs) {
		mIsFileCorrect = false;
		return;
	}

	mNumberOfDOF = DOF;

	mStream.readLine();
}

bool ActionLoader::isValueCorrect(const int &val) const
{
	return (val >= 0 && val <= 180);
}
