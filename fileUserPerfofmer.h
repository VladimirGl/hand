#ifndef FILEUSERPERFOFMER_H
#define FILEUSERPERFOFMER_H

#include <QObject>
#include <QList>

class UserFileSaver;
class UserFileLoader;
class User;

class QString;

class FileUserPerformer : public QObject
{
	Q_OBJECT
public:
	FileUserPerformer();

	~FileUserPerformer();

	QString currentFileName() const { return mFileName; }

	void startSave(const QString &fileName);
	void saveUser(User *user);
	void stopSave();

	void startLoad(const QString &fileName);
	User *loadUser();
	void stopLoad();

protected:
	void loadAllDOF();
	void loadAllConformity();

private:
	bool mIsStartSave;
	bool mIsStartLoad;

	QString mFileName;

	UserFileSaver *mSaver;
	UserFileLoader *mLoader;

	User *mUser;
};
#endif // FILEUSERPERFOFMER_H
