#include "agentwidget.h"
#include "ui_agentwidget.h"

AgentWidget::AgentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AgentWidget)
{
    ui->setupUi(this);
}

AgentWidget::~AgentWidget()
{
    delete ui;
}
