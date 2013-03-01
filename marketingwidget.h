#ifndef MARKETINGWIDGET_H
#define MARKETINGWIDGET_H

#include <QWidget>

class QCheckBox;

class MarketingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MarketingWidget(QWidget *parent = 0);
    ~MarketingWidget();
    QString getListStr();
    QList<int> getList();
private:
    QList<QCheckBox*> list;
};

#endif // MARKETINGWIDGET_H
