#include "decisionwidget.h"
#include "ui_decisionwidget.h"

DecisionWidget::DecisionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecisionWidget)
{
    ui->setupUi(this);
}

DecisionWidget::~DecisionWidget()
{
    delete ui;
}
