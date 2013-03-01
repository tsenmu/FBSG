#ifndef DECISIONWIDGET_H
#define DECISIONWIDGET_H

#include <QWidget>

namespace Ui {
class DecisionWidget;
}

class Player;

class DecisionWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DecisionWidget(Player *player, int round = 1, QWidget *parent = 0);
    ~DecisionWidget();
    
public slots:
private:
    Ui::DecisionWidget *ui;
    Player* player;
};

#endif // DECISIONWIDGET_H
