#ifndef MARKETSWIDGET_H
#define MARKETSWIDGET_H

#include <QWidget>

class MarketsDelegate;

namespace Ui {
class MarketsWidget;
}

class MarketsWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MarketsWidget(QWidget *parent = 0);
    ~MarketsWidget();
    
private:
    Ui::MarketsWidget *ui;
    MarketsDelegate* delegate;
};

#endif // MARKETSWIDGET_H
