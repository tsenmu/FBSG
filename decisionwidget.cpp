#include "decisionwidget.h"
#include "ui_decisionwidget.h"
#include "player.h"
#include <QSpinBox>
#include <QDesktopWidget>

DecisionWidget::DecisionWidget(QHash<QString, QString> *record, QWidget *parent) :
    QWidget(parent, Qt::Tool),
    ui(new Ui::DecisionWidget)
{
    ui->setupUi(this);
    this->record = record;

    QList<QSpinBox*> spinBoxes;
    spinBoxes << ui->loan << ui->numEngineers << ui->numWorkers << ui->salEngineers << ui->salWorkers
                 << ui->productCount << ui->productPrice << ui->productResearch << ui->supportCost;
    foreach(QSpinBox* item, spinBoxes)
    {
        QString key = item->whatsThis();
        if(record->contains(key))
        {
            int val = (*record)[key].toInt();
            if(key == "loan")
            {
                if(val < 0)
                {
                    val = -val;
                    ui->isPayback->setChecked(true);
                    ui->isLend->setChecked(false);
                }
            }
            item->setValue(val);
        }
        connect(item, SIGNAL(valueChanged(int)), SLOT(spinBoxChanged(int)));
    }

    connect(ui->isLend, SIGNAL(clicked()), SLOT(isLoanChanged()));
    connect(ui->isPayback, SIGNAL(clicked()), SLOT(isLoanChanged()));

    connect(ui->agentAdd, SIGNAL(changed()), SLOT(agentsChanged()));
    connect(ui->agentRemove, SIGNAL(changed()), SLOT(agentsChanged()));
    ui->agentAdd->setRecord((*record)["saleAgentAdded"]);
    ui->agentRemove->setRecord((*record)["saleAgentRemoved"]);
    ui->marketReport->setRecord((*record)["marketReportOrdered"]);
    agentsChanged();

    if((*record)["hireConsultant"] == "1")
        ui->hiredConsultant->setChecked(true);
}

void DecisionWidget::agentsChanged()
{
    QSet<int> set = ui->agentAdd->getSet().intersect(ui->agentRemove->getSet());
    ui->agentAdd->highlight(set);
    ui->agentRemove->highlight(set);
}

DecisionWidget& DecisionWidget::setPlayerName(QString name)
{
    ui->team->setText(name);
    setWindowTitle("Decision of " + name);
    return *this;
}

DecisionWidget& DecisionWidget::setRoundNumber(int num)
{
    ui->quarter->setText(QString::number(num));
    return *this;
}

void DecisionWidget::isLoanChanged()
{
    int value = ui->loan->value();
    if(ui->isPayback->isChecked())
    {
        value = -value;
    }
    (*record)["loan"] = QString::number(value);
}

void DecisionWidget::spinBoxChanged(int)
{
    QSpinBox* item = dynamic_cast<QSpinBox*>(sender());
    Q_ASSERT(item != 0);
    int value = item->value();
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
