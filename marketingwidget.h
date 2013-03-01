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
    void setRecord(QString& record);
    void highlight(const QSet<int>&);
    QString getListStr();
    QSet<int> getSet();
signals:
    void changed();
private slots:
    void change();
private:
    QList<QCheckBox*> list;
    QString* record;
};

#endif // MARKETINGWIDGET_H
