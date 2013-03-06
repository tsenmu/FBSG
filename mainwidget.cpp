#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "playermanager.h"
#include "config.h"
#include "coordinator.h"
#include "decisionwidget.h"
#include <QDesktopWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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
        Player &p = PlayerManager::getManager().getPlayer(model->data(model->index(row, 0)).toString());
        DecisionWidget* dec = new DecisionWidget(&p.record);
        dec->setPlayerName(p.name);
        dec->setRoundNumber(Coordinator::getCoordinator().runningRound());
        dec->show();
    }
}

void MainWidget::on_pushButton_runNextRound_clicked()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.nextRunningConf();
    coord.runCore("start loan hire produce sales end report");
    updateUI();
}

void MainWidget::on_pushButton_restorePreviousRound_clicked()
{
    int ret = QMessageBox::warning(this, "Warning", "Restoring previous round will cause current round to be removed permanently. Do you want to continue?", QMessageBox::Yes, QMessageBox::No);
    if(ret != QMessageBox::Yes)
    {
        return;
    }
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
    PlayerManager &pm = PlayerManager::getManager();
    for(int i = 0, c = model->rowCount(); i < c; i++)
    {
        QString name = model->data(model->index(i, 0)).toString();
        Player& p = pm.getPlayer(name);
        model->setData(model->index(i, 1), p.cash - p.loan);
    }
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
        QStandardItem* itemPlayer = new QStandardItem;
        itemPlayer->setText(player);
        QStandardItem* itemBalance = new QStandardItem;
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

void MainWidget::on_pushButton_saveReport_clicked()
{
    QString path = QFileDialog::getExistingDirectory();
    if(path.isEmpty())
        return;
    QStringList list;
    foreach(QString item, QDir().entryList())
    {
        if(item.endsWith(".html"))
            list.append(item);
    }
    for(int i = 0, c = list.size(); i < c; i++)
    {
        QProcess proc;
        QString name = list.at(i);
        name.chop(4);
        proc.start("./SaveReports.exe", QStringList() << path + "/" + name + "pdf" << name + "html");
        proc.waitForFinished();
    }
}
