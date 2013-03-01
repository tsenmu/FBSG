#ifndef MARKETINGWIDGET_H
#define MARKETINGWIDGET_H

#include <QWidget>

namespace Ui {
class MarketingWidget;
}

class MarketingWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MarketingWidget(QWidget *parent = 0);
    ~MarketingWidget();
    
private:
    Ui::MarketingWidget *ui;
};

#endif // MARKETINGWIDGET_H
