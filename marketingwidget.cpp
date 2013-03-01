#include "marketingwidget.h"
#include "ui_marketingwidget.h"

MarketingWidget::MarketingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MarketingWidget)
{
    ui->setupUi(this);
}

MarketingWidget::~MarketingWidget()
{
    delete ui;
}
