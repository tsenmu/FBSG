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
    void loadRunningConf();
    void saveRunningConf();
    void initRunningConf();
    void runCore(QString command);
signals:
    
public slots:

private:
    explicit Coordinator(const QString& defaultConf,
                         const QString& currentConf,
                         const QString& tempDir,QObject *parent = 0);
    static Coordinator* coord;
    QString defaultConfigurationFile;
    QString currentConfigurationFile;
    QString runningConfigurationFile;
    QString tempDirectory;
    QString running_gid;
    int running_rid;

};

#endif // COORDINATOR_H
