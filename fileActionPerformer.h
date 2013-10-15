#ifndef ACTIONPERFOMER_H
#define ACTIONPERFOMER_H

#include <QObject>
#include <QList>

class ActionSaver;
class ActionLoader;

class QString;
class QTimer;

class FileActionPerformer : public QObject
{
	Q_OBJECT
public:
	FileActionPerformer();

	~FileActionPerformer();

	bool hasSaver() const { return mSaver != NULL; }
	bool hasLoader() const { return mLoader != NULL; }

	bool isSaved() const { return mIsStartSave; }
	bool isLoaded() const { return mIsStartLoad; }
	bool isWork() const { return (isSaved() || isLoaded()); }

	QString currentFileName() const { return mFileName; }

	void startSave(const int &freq
			, const int &numOfDOF
			, const QString &fileName);
	void writeData(const QList<int> &data);
	void stopSave();

	void startLoad(const QString &fileName);
	QList<int> data();
	bool isFileEnd() const;
	bool isFileCorrect() const;
	void stopLoad();

signals:
	void onReadyLoad();

private slots:
	void isTime() { mIsTime = true; }

private:
	bool mIsStartSave;
	bool mIsStartLoad;

	bool mIsTime;

	QString mFileName;

	int mFreq;

	QTimer *mTimer;

	ActionSaver *mSaver;
	ActionLoader *mLoader;
};

#endif // ACTIONPERFOMER_H
