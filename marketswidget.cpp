#include "marketswidget.h"
#include "ui_marketswidget.h"

MarketsWidget::MarketsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketsWidget)
{
    ui->setupUi(this);
}

MarketsWidget::~MarketsWidget()
{
    delete ui;
}
