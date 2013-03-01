#ifndef CONFIG_H
#define CONFIG_H

#include <QHash>
#include <QString>
#include <QStringList>

class Config
{
public:
    static Config& getConfig();
    static void test();
    void read(QDataStream& in);
    void read(QString filename);
    void write(QDataStream& out);
    void write(QString filename);
    void set(QString key, QString value);
    void genDefault();
    QString get(QString key);
    QString getMarket(int index);
    QStringList getSetOfMarkets();
    void setSetOfMarkets(const QStringList list);
    QStringList getPlayers();
    void setPlayers(const QStringList& list);
    void setMarkets(const QStringList& list);
private:
    QStringList markets;
    explicit Config();
    static Config config;
    QHash<QString,QString> hash;
};

#endif // CONFIG_H


