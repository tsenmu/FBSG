#include "startwidget.h"
#include "ui_startwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include "marketsdialog.h"
#include "coordinator.h"
#include "config.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    ui->status->set(0);

    connect(ui->widget, SIGNAL(reachLimit()), this, SLOT(reachLimit_emitted()));
    connect(ui->widget, SIGNAL(itemChanged()), this, SLOT(itemChanged_emitted()));
}

StartWidget::~StartWidget()
{
    delete ui;
}

void StartWidget::itemChanged_emitted()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadRunningConf();
    Config& conf = Config::getConfig();
    conf.setPlayers(ui->widget->items());
    coord.saveRunningConf();
}

void StartWidget::ini()
{
    /* Create a brand new running config file based on timestamp now.*/
    Coordinator& coord = Coordinator::getCoordinator();
    coord.initRunningConf();

    /* Empty player and market list. */
    Config& conf = Config::getConfig();
    conf.setPlayers(QStringList());
    conf.setMarkets(QStringList());
    coord.saveRunningConf();

    /* Ui update. */
    int size = conf.getSetOfMarkets().size();
    ui->widget->on_pushButton_clear_clicked();
    ui->widget->setVar("player", "Player", "players", "Players", size);
    ui->widget->setLabelDynamic(QString("0/%1").arg(size));
}


void StartWidget::on_pushButton_startGame_clicked()
{
    if(ui->widget->items().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "At least one player need to be added.");
        return;
    }
    MarketsDialog dialog;
    int ret = dialog.exec();
    if(ret != QDialog::Accepted)
    {
        return;
    }

    Coordinator& coord = Coordinator::getCoordinator();
    coord.saveRunningConf();
    coord.runCore("init");
    emit startGame();
}

void StartWidget::on_pushButton_backToMenu_clicked()
{
    emit backToMenu();
}

void StartWidget::reachLimit_emitted()
{
    QMessageBox::warning(this, "Warning", "You have reached the limit of player number. "
                         "Add markets in configuration if more players are needed.");
}
