#include "config.h"
#include <QString>
#include <QHash>
#include <QDataStream>
#include <QFile>
#include <QDebug>


Config Config::config;

Config::Config()
{

}

Config &Config::getConfig()
{
    return config;
}

void Config::clear()
{
    hash.clear();
}

void Config::read(QDataStream& in)
{
    in >> hash;
}

void Config::read(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    read(in);
    file.close();
}

void Config::write(QDataStream& out)
{
    out << hash;
}

void Config::write(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    write(out);
    file.close();
}

void Config::set(QString key, QString value)
{
    hash[key] = value;
}

QString Config::get(QString key)
{
    return hash[key];
}

void Config::test()
{

}

QString Config::getMarket(int index)
{
    QStringList markets = getMarkets();
    return markets[index];
}

QStringList Config::getMarkets()
{
    QStringList markets = get("markets").split(";;");
    return markets;
}

QStringList Config::getPlayers() {
    return get("players").split(";;");
}

QStringList Config::getSetOfMarkets()
{
    return get("Set of markets").split(";;");
}

void Config::setSetOfMarkets(const QStringList list)
{
    QString val;
    foreach(QString str, list)
    {
        val.push_back(str);
        val.push_back(";;");
    }
    val.chop(2);
}

void Config::genDefault()
{
    hash["Set of markets"] = "Hangzhou;;Wuhan;;Nanjing;;Shenyang;;Chengdu;;Xi'an";
    hash["Month in a quarter"] = QString::number(3);
    hash["Days in a month"] = QString::number(30);
    hash["Working hours in a month"] = QString::number(168);
    hash["Set of markets"] = "Hangzhou;;Wuhan;;Nanjing;;Shenyang;;Chengdu;;Xi'an";
    hash["Hours in a component"] = QString::number(4);
    hash["Workers in a component"] = QString::number(1);
    hash["Engineers in a product"] = QString::number(4);
    hash["Hours in a product"] = QString::number(4);
    hash["Components in a product"] = QString::number(4);
    hash["Material cost per component"] = QString::number(200);
    hash["Material cost per product"] = QString::number(100);
    hash["Component storage cost per quarter"] = QString::number(50);
    hash["Product storage cost per quarter"] = QString::number(50);
    hash["Market population"] =  QString::number(1000000);
    hash["Penetration"] = QString::number(0.03);
    hash["Market report cost per market quarter"] = QString::number(500000);
    hash["Balance upper limit to have bank loans"] = QString::number(5000000);
    hash["Bank loan upper limit while positive balance"] = QString::number(5000000);
    hash["Bank loan upper limit while negative balance"] = QString::number(10000000);
    hash["Interest per quarter"] = QString::number(0.025);
    hash["Consultant cost per 30 minutes"] = QString::number(1000000);
    hash["Product price minimum"] = QString::number(1);
    hash["Product price maximum"] = QString::number(15000);
    hash["Initial cash"] = QString::number(10000000);
    hash["Salary minimum"] = QString::number(0);
    hash["Salary maximum"] = QString::number(30000);
    hash["Adding agent cost"] = QString::number(500000);
    hash["Removing agent cost"] = QString::number(250000);
}

void Config::setPlayers(const QStringList &list)
{
    QString var;
    foreach(QString str, list)
    {
        var.push_back(str);
        var.push_back(";;");
    }
    var.chop(2);
    set("players", var);
}

void Config::setMarkets(const QStringList &list)
{
    QString var;
    foreach(QString str, list)
    {
        var.push_back(str);
        var.push_back(";;");
    }
    var.chop(2);
    set("markets", var);
}
