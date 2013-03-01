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
        connect(item, SIGNAL(clicked()), SLOT(change()));
    }
    setLayout(layout);
}

MarketingWidget::~MarketingWidget()
{
}

void MarketingWidget::highlight(const QSet<int>& set)
{
    int index = 0;
    foreach(QCheckBox* item, list)
    {
        if(set.contains(index))
            item->setStyleSheet("background: #F22");
        else
            item->setStyleSheet("");
        index++;
    }
}

void MarketingWidget::change()
{
    *record = getListStr();
    emit changed();
}

QString MarketingWidget::getListStr()
{
    QStringList ret;
    foreach(int item, getSet())
    {
        ret.append(QString::number(item));
    }
    return ret.join(";;");
}

QSet<int> MarketingWidget::getSet()
{
    QSet<int> ret;
    int index = 0;
    foreach(QCheckBox* item, list)
    {
        if(item->isChecked())
        {
            ret.insert(index);
        }
        index++;
    }
    return ret;
}


void MarketingWidget::setRecord(QString& record)
{
    this->record = &record;
    foreach(QCheckBox* item, list)
    {
        item->setChecked(false);
    }

    if(!record.isEmpty())
        foreach(QString s, record.split(";;"))
        {
            int i = s.toInt();
            list[i]->setChecked(true);
        }
}
