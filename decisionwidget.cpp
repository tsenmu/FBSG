#include "decisionwidget.h"
#include "ui_decisionwidget.h"
#include "player.h"
#include <QSpinBox>

DecisionWidget::DecisionWidget(Player *player, int round, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecisionWidget)
{
    ui->setupUi(this);
    ui->quarter->setText("Quarter " + QString::number(round));
    this->player = player;

    QList<QSpinBox*> spinBoxes;
    spinBoxes << ui->loan;
    foreach(QSpinBox* item, spinBoxes)
    {

    }
}

DecisionWidget::~DecisionWidget()
{
    delete ui;
}
