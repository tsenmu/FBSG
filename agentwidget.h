#ifndef AGENTWIDGET_H
#define AGENTWIDGET_H

#include <QWidget>

namespace Ui {
class AgentWidget;
}

class AgentWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit AgentWidget(QWidget *parent = 0);
    ~AgentWidget();
    
private:
    Ui::AgentWidget *ui;
};

#endif // AGENTWIDGET_H
