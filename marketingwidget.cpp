#include "marketingwidget.h"
#include "flowlayout.h"
#include "config.h"
#include <QCheckBox>
#include <QDebug>

MarketingWidget::MarketingWidget(QWidget *parent) :
    QWidget(parent)
{
    FlowLayout *layout = new FlowLayout;
    foreach(QString market, Config::getConfig().getMarkets()) {
        QCheckBox *item = new QCheckBox(market, this);
        list.append(item);
        layout->addWidget(item);
        connect(item, SIGNAL(clicked(bool)), SLOT(change()));
    }
    setLayout(layout);
}

MarketingWidget::~MarketingWidget()
{
}

void MarketingWidget::change()
{
    *record = getListStr();
}

QString MarketingWidget::getListStr()
{
    QStringList ret;
    foreach(int item, getList())
    {
        ret.append(QString::number(item));
    }
    return ret.join(";;");
}

QList<int> MarketingWidget::getList()
{
    QList<int> ret;
    int index = 0;
    foreach(QCheckBox* item, list)
    {
        if(item->isChecked())
        {
            ret.append(ret);
        }
        index++;
    }
    return ret;
}


void MarketingWidget::setRecord(QString* record)
{
    this->record = record;
    foreach(QCheckBox* item, list)
    {
        item->setChecked(false);
    }

    foreach(QString s, (*record).split(";;"))
    {
        int i = s.toInt();
        list[i]->setChecked(true);
    }
}
