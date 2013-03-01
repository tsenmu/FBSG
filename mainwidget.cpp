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
    model->setColumnCount(2);
    QStringList headerList;
    headerList << "Player" << "Balance";
    model->setHorizontalHeaderLabels(headerList);
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

void MainWidget::ini()
{
    model->clear();
    Coordinator& coord = Coordinator::getCoordinator();
    Config& conf = Config::getConfig();
    foreach(QString player, conf.getPlayers())
    {
        qDebug() << player;
        QList<QStandardItem*> items;
        QStandardItem* itemPlayer = new QStandardItem();
        itemPlayer->setText(player);
        QStandardItem* itemBalance = new QStandardItem();
        itemBalance->setText("0");
        items << itemPlayer<< itemBalance;
        model->appendRow(items);
    }
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

