#include "marketswidget.h"
#include "ui_marketswidget.h"
#include "marketsdelegate.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include "config.h"
#include "coordinator.h"
#include <QDebug>

MarketsWidget::MarketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketsWidget)
{
    ui->setupUi(this);
    delegate = new MarketsDelegate(this);
    ui->tableView->setItemDelegate(delegate);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
}

void MarketsWidget::ini()
{
    qDebug() << "aaa";
    model->clear();
    setOfMarkets.clear();
    model->setColumnCount(2);
    QStringList headerList;
    headerList << "Player" << "Markets";
    model->setHorizontalHeaderLabels(headerList);

    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadRunningConf();
    Config& conf = Config::getConfig();
    QStringList marketList = conf.getSetOfMarkets();

    foreach(QString str, marketList)
    {
        setOfMarkets.insert(str);
    }

    updatePlayerMarketMap();

    QStringList list = conf.getPlayers();
    foreach(QString str, list)
    {
        QStandardItem* itemPlayer = new QStandardItem(str);
        QStandardItem* itemMarket = new QStandardItem(playerMarketMap[str]);
        QList<QStandardItem*> itemList;
        itemList << itemPlayer << itemMarket;
        model->appendRow(itemList);
    }
}

MarketsWidget::~MarketsWidget()
{
    delete ui;
}

void MarketsWidget::updatePlayerMarketMap()
{

}
