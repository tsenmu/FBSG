#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coordinator.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initStackedWidget();
    Coordinator::getCoordinator();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_newGame_triggered()
{
    ui->page_start->ini();
    switchToPage(pageMap[ui->page_start]);
}

void MainWindow::on_action_close_triggered()
{
    this->close();
}

void MainWindow::on_action_loadGame_triggered()
{

}

void MainWindow::on_action_about_triggered()
{

}

void MainWindow::on_action_configuration_triggered()
{
    ui->page_conf->ini();
    switchToPage(pageMap[ui->page_conf]);
}

void MainWindow::switchToPage(int index)
{
    previousIndex = ui->stackedWidget->currentIndex();
    ui->stackedWidget->setCurrentIndex(index);

    if(index == pageMap[ui->page_main])
    {
        ui->action_configuration->setEnabled(false);
    }
    else
    {
        ui->action_configuration->setEnabled(true);
    }
}

void MainWindow::back_emitted()
{
    this->switchToPage(previousIndex);
}

void MainWindow::startGame_emitted()
{
    this->switchToPage(pageMap[ui->page_main]);
    ui->page_main->ini();
}

void MainWindow::endGame_emitted()
{
    this->switchToPage(pageMap[ui->page_end]);
}

void MainWindow::initStackedWidget()
{
    int cnt = ui->stackedWidget->count();
    for(int i = 0; i < cnt; ++i)
    {
        pageMap[ui->stackedWidget->widget(i)] = i;
    }
    switchToPage(0);
    previousIndex = 0;
    connect(ui->page_conf, SIGNAL(back()), this, SLOT(back_emitted()));
    connect(ui->page_menu, SIGNAL(loadGame()), this, SLOT(on_action_loadGame_triggered()));
    connect(ui->page_menu, SIGNAL(newGame()), this, SLOT(on_action_newGame_triggered()));
    connect(ui->page_start, SIGNAL(startGame()), this, SLOT(startGame_emitted()));
    connect(ui->page_main, SIGNAL(endGame()), this, SLOT(endGame_emitted()));
    connect(ui->page_start, SIGNAL(backToMenu()), this, SLOT(backToMenu_emitted()));
    connect(ui->page_main, SIGNAL(backToMenu()), this, SLOT(backToMenu_emitted()));
    connect(ui->page_end, SIGNAL(backToMenu()), this, SLOT(backToMenu_emitted()));

}

void MainWindow::backToMenu_emitted()
{
    this->switchToPage(pageMap[ui->page_menu]);
}



