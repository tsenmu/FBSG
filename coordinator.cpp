#include "coordinator.h"
#include "config.h"
#include <QDateTime>

Coordinator* Coordinator::coord = 0;

Coordinator::Coordinator(const QString& defaultConf,
                         const QString& currentConf,
                         const QString& tempDir,
                         QObject *parent) : QObject(parent)
{
    defaultConfigurationFile = defaultConf;
    currentConfigurationFile = currentConf;
    tempDirectory = tempDir;
    loadCurrentConf();
}

Coordinator& Coordinator::getCoordinator()
{
    if(coord == 0)
        coord = new Coordinator("./config/default.conf","./config/current.conf",
                                "./temp/", 0);
    return *coord;
}

void Coordinator::loadCurrentConf()
{
    Config& conf = Config::getConfig();
    conf.read(currentConfigurationFile);
}

void Coordinator::loadDefaultConf()
{
    Config& conf = Config::getConfig();
    conf.read(defaultConfigurationFile);
}

void Coordinator::saveCurrentConf()
{
    Config& conf = Config::getConfig();
    conf.write(currentConfigurationFile);
}

void Coordinator::loadRunningConf()
{
    Config& conf = Config::getConfig();
    conf.read(runningConfigurationFile);
}

void Coordinator::saveRunningConf()
{
    Config& conf = Config::getConfig();
    conf.write(runningConfigurationFile);
}

void Coordinator::initRunningConf()
{
    loadCurrentConf();
    Config& conf = Config::getConfig();
    QString gid = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
    QString rid = QString::number(0);
    runningConfigurationFile = tempDirectory + gid + "_" + rid + ".rconf";
    saveRunningConf();
}
