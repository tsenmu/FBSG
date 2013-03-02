#ifndef MARKETSWIDGET_H
#define MARKETSWIDGET_H

#include <QWidget>
#include <QSet>
#include <QHash>

class MarketsDelegate;
class QStandardItemModel;
namespace Ui {
class MarketsWidget;
}

class MarketsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MarketsWidget(QWidget *parent = 0);
    ~MarketsWidget();
    void ini();
    
private:
    Ui::MarketsWidget *ui;
    MarketsDelegate* delegate;
    QStandardItemModel* model;
    QSet<QString> setOfMarkets;
    QHash<QString, QString> playerMarketMap;

    void updatePlayerMarketMap();

};

#endif // MARKETSWIDGET_H
