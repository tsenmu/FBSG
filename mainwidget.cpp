#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDesktopWidget>
#include <QStandardItemModel>
#include "config.h"
#include "coordinator.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->status->set(1);
    model = new QStandardItemModel(this);
    ui->tableView->setModel(model);
    model->setRowCount(0);
    model->setColumnCount(1);
    Coordinator& coord = Coordinator::getCoordinator();
    //for(int i = 0; i < )
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

