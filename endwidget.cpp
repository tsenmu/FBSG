#include "endwidget.h"
#include "ui_endwidget.h"

EndWidget::EndWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EndWidget)
{
    ui->setupUi(this);
    ui->status->set(2);
}

EndWidget::~EndWidget()
{
    delete ui;
}

void EndWidget::on_pushButton_backToMenu_clicked()
{
    emit backToMenu();
}
