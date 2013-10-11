#include "fileActionPerfomer.h"

#include "actionLoader.h"
#include "actionSaver.h"

#include <QTimer>

FileActionPerfomer::~FileActionPerfomer()
{
	if (mSaver != NULL) {
		delete mSaver;
		mSaver = NULL;
	}

	if (mLoader != NULL) {
		delete mLoader;
		mLoader = NULL;
	}
}

void FileActionPerfomer::startSave(const int &freq, const int &numOfDOF, const QString &fileName)
{
	if (mIsStartLoad) {
		return;
	}

	mSaver = new ActionSaver(freq, numOfDOF, fileName);
	mFileName = fileName;
	mIsStartSave = true;
	mIsTime = true;
	mFreq = freq;
}

void FileActionPerfomer::writeData(const QList<int> &data)
{
	if (!mIsStartSave) {
		return;
	}

	if (!mIsTime) {
		return;
	}

	mIsTime = false;
	QTimer::singleShot(mFreq, this, SLOT(isTime()));

	mSaver->writeData(data);
}

void FileActionPerfomer::stopSave()
{
	mFreq = 0;
	mIsTime = false;
	mIsStartSave = false;
	mFileName = "\n";

	mSaver->stopRecord();

	delete mSaver;
	mSaver = NULL;
}

void FileActionPerfomer::startLoad(const QString &fileName)
{
	if (mIsStartSave) {
		return;
	}

	mLoader = new ActionLoader(fileName);
	mFileName = fileName;
	mIsStartLoad = true;
	mFreq = mLoader->freq();

	mTimer = new QTimer(this);
	connect(mTimer, SIGNAL(timeout()), this, SIGNAL(onReadyLoad()));
	mTimer->start(mFreq);
}

QList<int> FileActionPerfomer::data()
{
	mLoader->data();
}

bool FileActionPerfomer::isFileEnd() const
{
	if (!mIsStartLoad) {
		return true;
	}

	mLoader->isFileEnd();
}

bool FileActionPerfomer::isFileCorrect() const
{
	if (!mIsStartLoad) {
		return true;
	}

	mLoader->isFileCorrect();
}

void FileActionPerfomer::stopLoad()
{
	mFreq = 0;
	mIsStartLoad = false;
	mFileName = "\n";

	disconnect(mTimer, SIGNAL(timeout()), this, SIGNAL(onReadyLoad()));
	mTimer->stop();

	delete mLoader;
	mLoader = NULL;
}

