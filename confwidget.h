#ifndef CONFWIDGET_H
#define CONFWIDGET_H

#include <QWidget>

namespace Ui {
class ConfWidget;
}

class ConfWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConfWidget(QWidget *parent = 0);
    ~ConfWidget();

public slots:
    void on_pushButton_back_clicked();
    void on_pushButton_apply_clicked();
    void on_pushButton_default_clicked();
    void ini();



signals:
    void back();
    
private:
    Ui::ConfWidget *ui;
    void loadFromConf();
    void saveToConf();
    bool changed();
};

#endif // CONFWIDGET_H
