#include "decisionwidget.h"
#include "ui_decisionwidget.h"
#include "player.h"
#include <QSpinBox>

DecisionWidget::DecisionWidget(QHash<QString, QString> *record, int round, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DecisionWidget)
{
    ui->setupUi(this);
    ui->quarter->setText("Quarter " + QString::number(round));
    this->record = record;

    QList<QSpinBox*> spinBoxes;
    spinBoxes << ui->loan << ui->numEngineers << ui->numWorkers << ui->salEngineers << ui->salWorkers
                 << ui->productCount << ui->productPrice << ui->productResearch << ui->supportCost;
    foreach(QSpinBox* item, spinBoxes)
    {
        if(record->contains(item->whatsThis()))
            item->setValue((*record)[item->whatsThis()].toInt());
        connect(item, SIGNAL(valueChanged(int)), SLOT(spinBoxChanged(int)));
    }
    ui->agentAdd->setRecord(&(*record)["saleAgentAdded"]);
    ui->agentRemove->setRecord(&(*record)["saleAgentRemoved"]);
    ui->marketReport->setRecord(&(*record)["marketReportOrdered"]);
}

void DecisionWidget::spinBoxChanged(int value)
{
    QSpinBox* item = dynamic_cast<QSpinBox*>(sender());
    Q_ASSERT(item != 0);
    QString key = item->whatsThis();
    if(key == "loan" && ui->isPayback->isChecked())
        value = -value;
    (*record)[key] = QString::number(value);
}

DecisionWidget::~DecisionWidget()
{
    delete ui;
}

QHash<QString, QString>& DecisionWidget::getRecord()
{
    return *record;
}

void DecisionWidget::on_hiredConsultant_clicked(bool checked)
{
    (*record)["hireConsultant"] = checked ? "1" : "0";
}
