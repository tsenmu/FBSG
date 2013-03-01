#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <QHash>

class Player
{
public:
    QString name;
    qint64 cash;
    qint64 loan;
    int homeMarket;
    QHash<int, int> marketAgents;
    QHash<QString, QString> record;
    static QHash<QString, QString> globalRecord;
};

#endif // PLAYER_H
