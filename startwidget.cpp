#include "startwidget.h"
#include "ui_startwidget.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>
#include "coordinator.h"
#include "config.h"

StartWidget::StartWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWidget)
{
    ui->setupUi(this);
    Coordinator::getCoordinator();
    Config& conf = Config::getConfig();
    int size = conf.getSetOfMarkets().size();
    ui->widget->setVar("player", "Player", "players", "Players", size);
    ui->status->set(0);
    ui->widget->setLabelDynamic(QString("0/%1").arg(size));
    ui->widget_markets->setVisible(false);
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
    ui->widget_markets->ini();
}

void StartWidget::ini()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.initRunningConf();
    Config& config = Config::getConfig();
}


void StartWidget::on_pushButton_startGame_clicked()
{
    if(ui->widget->items().size() == 0)
    {
        QMessageBox::warning(this, "Warning", "At least one player need to be added.");
        return;
    }
    Coordinator& coord = Coordinator::getCoordinator();
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

void StartWidget::on_pushButton_markets_clicked()
{
    ui->widget_markets->ini();
    ui->widget_markets->setVisible(!ui->widget_markets->isVisible());
    ui->pushButton_markets->setText(ui->widget_markets->isVisible() ? "Markets <<" : "Markets >>");
}
