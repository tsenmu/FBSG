#ifndef DECISIONWIDGET_H
#define DECISIONWIDGET_H

#include <QWidget>

namespace Ui {
class DecisionWidget;
}

class DecisionWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DecisionWidget(QWidget *parent = 0);
    ~DecisionWidget();
    
private:
    Ui::DecisionWidget *ui;
};

#endif // DECISIONWIDGET_H
