#include "mainwidget.h"
#include "ui_mainwidget.h"
#include <QDesktopWidget>
#include "coordinator.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    ui->status->set(1);
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

