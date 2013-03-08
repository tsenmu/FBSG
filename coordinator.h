#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <QObject>

class Coordinator : public QObject
{
    Q_OBJECT
public:
    static Coordinator& getCoordinator();
    void loadCurrentConf();
    void loadDefaultConf();
    void saveCurrentConf();

    bool hasLostRunningConf();
    void loadLostRunningConf();
    void loadRunningConf();
    void saveRunningConf();
    void initRunningConf(const int round = 0);
    void nextRunningConf();
    void previousRunningConf();
    void saveToFile(const QString& fileName);
    void loadFromFile(const QString& fileName);
    int runningRound();

    void clearTempDirectory();
    QStringList runningRounds() const;
    void runCore(QString command);

    void check();


signals:
    
public slots:

private:
    explicit Coordinator(const QString& defaultConf,
                         const QString& currentConf,
                         const QString& tempDir,
                         const QString& confDir,
                         QObject *parent = 0);
    static Coordinator* coord;
    QString defaultConfigurationFile;
    QString currentConfigurationFile;
    QString runningConfigurationFile;
    QString confDirectory;
    QString tempDirectory;
    QString running_gid;
    QString running_rid;

    void inline genConfFile();
};

#endif // COORDINATOR_H
