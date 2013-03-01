#ifndef ENDWIDGET_H
#define ENDWIDGET_H

#include <QWidget>

namespace Ui {
class EndWidget;
}

class EndWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit EndWidget(QWidget *parent = 0);
    ~EndWidget();

public slots:
    void on_pushButton_backToMenu_clicked();

signals:
    void backToMenu();
    
private:
    Ui::EndWidget *ui;
};

#endif // ENDWIDGET_H
