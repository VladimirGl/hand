#include "fileUserPerfofmer.h"

#include "userFileLoader.h"
#include "userFileSaver.h"
#include "user.h"

FileUserPerformer::FileUserPerformer() :
	mIsStartSave(false),
	mIsStartLoad(false),
	mSaver(NULL),
	mLoader(NULL),
	mUser(NULL)
{}

FileUserPerformer::~FileUserPerformer()
{
	if (mSaver != NULL) {
		delete mSaver;
		mSaver = NULL;
	}

	if (mLoader != NULL) {
		delete mLoader;
		delete mUser;
		mLoader = NULL;
		mUser = NULL;
	}
}

void FileUserPerformer::startSave(const QString &fileName)
{
	if (mIsStartLoad) {
		return;
	}

	mSaver = new UserFileSaver(fileName);
	mFileName = fileName;
	mIsStartSave = true;
}

void FileUserPerformer::saveUser(User *user)
{
	if (!mIsStartSave) {
		return;
	}

	for (int i = 0; i < user->DOFSize(); i++) {
		mSaver->writeDOFData(user->sensorMin(i)
				, user->sensorMax(i));
	}

	for (int i = 0; i < user->conformitySize(); i++) {
		mSaver->writeConformityData(user->motorList(i));
	}
}

void FileUserPerformer::stopSave()
{
	mIsStartSave = false;
	mFileName = "\n";

	mSaver->stopWriteFile();

	delete mSaver;
	mSaver = NULL;
}

void FileUserPerformer::startLoad(const QString &fileName)
{
	if (mIsStartSave) {
		return;
	}

	mLoader = new UserFileLoader(fileName);
	mFileName = fileName;
	mIsStartLoad = true;

	mUser = new User;
}

User *FileUserPerformer::loadUser()
{
	if (!mIsStartLoad) {
		return NULL;
	}

	if (!mLoader->isFileCorrect()) {
		return NULL;
	}

	loadAllDOF();
	loadAllConformity();

	if (!mLoader->isFileCorrect()) {
		return NULL;
	}

	if (!mLoader->isFileEnd()) {
		return NULL;
	}

	return mUser;
}

void FileUserPerformer::loadAllDOF()
{
	if (!mIsStartLoad) {
		return;
	}

	while (mLoader->isDOFRead()) {
		QList<int> DOFList = mLoader->DOFList();

		mUser->addDOF(DOFList.at(0), DOFList.at(1));
	}
}

void FileUserPerformer::loadAllConformity()
{
	if (!mIsStartLoad) {
		return;
	}

	int count = 0;

	while (mLoader->isConformityRead()) {
		QList<int> conformityList = mLoader->conformityList();
		int size = conformityList.size();

		for (int i = 0; i < size; i++) {
			mUser->addSensorMotorConformity(count, conformityList.at(i));
		}

		count++;
	}
}

void FileUserPerformer::stopLoad()
{
	mIsStartLoad = false;
	mFileName = "\n";

	delete mLoader;
	mLoader = NULL;

	delete mUser;
	mUser = NULL;
}
