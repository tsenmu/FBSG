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
    }
    setLayout(layout);
}

MarketingWidget::~MarketingWidget()
{
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
    foreach(QCheckBox* item, list) {
        if(item->isChecked())
        {
            ret.append(ret);
        }
        index++;
    }
    return ret;
}
