#include "coordinator.h"
#include "config.h"
#include "playermanager.h"
#include <QDateTime>
#include <QFile>
#include <QDataStream>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <QDebug>

Coordinator* Coordinator::coord = 0;

Coordinator::Coordinator(const QString& defaultConf,
                         const QString& currentConf,
                         const QString& tempDir,
                         QObject *parent) : QObject(parent)
{
    defaultConfigurationFile = defaultConf;
    currentConfigurationFile = currentConf;
    tempDirectory = tempDir;
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
    QFile file(runningConfigurationFile);
    QRegExp number("[0-9]+");
    number.indexIn(runningConfigurationFile);
    running_gid = number.cap();
    number.indexIn(runningConfigurationFile, number.pos() + number.cap().length());
    running_rid = number.cap();
    if(file.open(QFile::ReadOnly))
    {
        conf.clear();
        QDataStream stream(&file);
        conf.read(stream);
        PlayerManager::getManager().read(stream);
    }
//    else
//    {
//        qDebug() << "Error reading file";
//    }
}

void Coordinator::saveRunningConf()
{
    Config& conf = Config::getConfig();
    QFile file(runningConfigurationFile);
    if(file.open(QFile::WriteOnly))
    {
        QDataStream stream(&file);
        conf.write(stream);
        PlayerManager::getManager().write(stream);
    }
}

void Coordinator::initRunningConf()
{
    loadCurrentConf();
    running_gid = QString::number(QDateTime::currentDateTime().toMSecsSinceEpoch());
    running_rid = QString::number(0);
    genConfFile();
    saveRunningConf();
}

void Coordinator::runCore(QString command)
{
    saveRunningConf();
    static const QString program =
#ifdef WINDOWS
    "core.exe";
#else
    "core";
#endif
    QStringList arg = command.split(" ");
    arg.prepend(":" + runningConfigurationFile);
    QProcess proc;
    proc.start("./" + program, arg);
    while(!proc.waitForFinished(100))
    {
        QApplication::instance()->processEvents();
    }
    loadRunningConf();
}

void inline Coordinator::genConfFile()
{
    runningConfigurationFile = tempDirectory + running_gid + "_" + QString().sprintf("%03d", running_rid.toInt()) + ".rconf";
}

void Coordinator::nextRunningConf()
{
    loadRunningConf();
    running_rid = QString::number(running_rid.toInt() + 1);
    genConfFile();
    saveRunningConf();
}

void Coordinator::previousRunningConf()
{
    int rid = running_rid.toInt();
    if(rid == 1) return;
    running_rid = QString::number(rid - 1);
    genConfFile();
    loadRunningConf();
}

QStringList Coordinator::runningRounds() const
{
    QStringList ret;
    QDir dir(tempDirectory);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().startsWith(running_gid) &&
                fileInfo.fileName().endsWith(".rconf"))
        {
            ret << fileInfo.fileName();
        }
    }
    return ret;
}

void Coordinator::clearTempDirectory()
{
    QDir dir(tempDirectory);
    QStringList list = dir.entryList();
    foreach(QString str, list)
    {
        if(str.endsWith(".rconf"))
        {
            dir.remove(str);
        }
    }
}

bool Coordinator::hasLostRunningConf()
{
    bool ret = false;
    QDir dir(tempDirectory);
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i)
    {
        QFileInfo fileInfo = list.at(i);
        if(fileInfo.fileName().endsWith(".rconf"))
        {
            ret = true;
            break;
        }
    }
    return ret;
}

void Coordinator::loadLostRunningConf()
{

    QDir dir(tempDirectory);
    runningConfigurationFile = dir.entryInfoList().last().filePath();
    loadRunningConf();
}

int Coordinator::runningRound()
{
    return running_rid.toInt() + 1;
}
