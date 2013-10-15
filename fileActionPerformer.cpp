#include "fileActionPerformer.h"

#include "actionLoader.h"
#include "actionSaver.h"

#include <QTimer>

FileActionPerformer::FileActionPerformer() :
	mIsStartSave(false),
	mIsStartLoad(false),
	mIsTime(false),
	mFreq(0),
	mSaver(NULL),
	mLoader(NULL)
{}

FileActionPerformer::~FileActionPerformer()
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

void FileActionPerformer::startSave(const int &freq, const int &numOfDOF, const QString &fileName)
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

void FileActionPerformer::writeData(const QList<int> &data)
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

void FileActionPerformer::stopSave()
{
	mFreq = 0;
	mIsTime = false;
	mIsStartSave = false;
	mFileName = "\n";

	mSaver->stopRecord();

	delete mSaver;
	mSaver = NULL;
}

void FileActionPerformer::startLoad(const QString &fileName)
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

QList<int> FileActionPerformer::data()
{
	return mLoader->data();
}

bool FileActionPerformer::isFileEnd() const
{
	if (!mIsStartLoad) {
		return true;
	}

	return mLoader->isFileEnd();
}

bool FileActionPerformer::isFileCorrect() const
{
	if (!mIsStartLoad) {
		return true;
	}

	return mLoader->isFileCorrect();
}

void FileActionPerformer::stopLoad()
{
	mFreq = 0;
	mIsStartLoad = false;
	mFileName = "\n";

	disconnect(mTimer, SIGNAL(timeout()), this, SIGNAL(onReadyLoad()));
	mTimer->stop();

	delete mLoader;
	mLoader = NULL;
}

