#include "marketswidget.h"
#include "ui_marketswidget.h"
#include "marketsdelegate.h"

MarketsWidget::MarketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketsWidget)
{
    ui->setupUi(this);
    delegate = new MarketsDelegate(this);
    ui->tableView->setItemDelegate(delegate);
}

MarketsWidget::~MarketsWidget()
{
    delete ui;
}
