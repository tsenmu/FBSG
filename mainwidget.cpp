#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDesktopWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include "config.h"
#include "coordinator.h"
#include <QDebug>
#include "decisionwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->status->set(1);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    QHeaderView *HorizonHdr = ui->tableView->horizontalHeader();
    HorizonHdr->setResizeMode(QHeaderView::Stretch);
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(doubleClicked(QModelIndex)));
}

void MainWidget::doubleClicked(const QModelIndex &ind)
{
    int row = ind.row();
    if(row >= 0 && row < model->rowCount())
    {
        static QHash<QString, QString> dummyRecord; // TODO remove this
        DecisionWidget* dec = new DecisionWidget(&dummyRecord);
        dec->show();
    }
}

void MainWidget::on_pushButton_runNextRound_clicked()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.nextRunningConf();
    updateUI();
}

void MainWidget::on_pushButton_restorePreviousRound_clicked()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.previousRunningConf();
    updateUI();

}

void MainWidget::updateUI()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadRunningConf();
    ui->label_round->setText(QString::number(coord.runningRound()));
    ui->pushButton_restorePreviousRound->setEnabled(coord.runningRound() != 1);
    ui->pushButton_saveReport->setEnabled(coord.runningRound() != 1);
}

void MainWidget::ini()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadRunningConf();
    Config& conf = Config::getConfig();
    /* Init the player list.*/
    model->clear();
    model->setColumnCount(2);
    QStringList headerList;
    headerList << "Player" << "Balance";
    model->setHorizontalHeaderLabels(headerList);
    foreach(QString player, conf.getPlayers())
    {
        QList<QStandardItem*> items;
        QStandardItem* itemPlayer = new QStandardItem();
        itemPlayer->setText(player);
        QStandardItem* itemBalance = new QStandardItem();
        itemBalance->setText("0");
        items << itemPlayer<< itemBalance;
        model->appendRow(items);
    }
    updateUI();
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::on_pushButton_endGame_clicked()
{
    emit endGame();
}

void MainWidget::on_pushButton_backToMenu_clicked()
{
    emit backToMenu();
}

