#include "menuwidget.h"
#include "ui_menuwidget.h"

MenuWidget::MenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuWidget)
{
    ui->setupUi(this);
}

MenuWidget::~MenuWidget()
{
    delete ui;
}

void MenuWidget::on_pushButton_exit_clicked()
{
    QApplication::closeAllWindows();
}

void MenuWidget::on_pushButton_loadGame_clicked()
{
    emit loadGame();
}

void MenuWidget::on_pushButton_newGame_clicked()
{
    emit newGame();
}

