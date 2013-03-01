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
    
signals:
    
public slots:

private:
    explicit Coordinator(const QString& defaultConf,
                         const QString& currentConf,
                         const QString& tempDir,QObject *parent = 0);
    static Coordinator* coord;
    QString defaultConfigurationFile;
    QString currentConfigurationFile;
    QString tempDirectory;
};

#endif // COORDINATOR_H
