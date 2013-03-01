#ifndef MENUWIDGET_H
#define MENUWIDGET_H

#include <QWidget>

namespace Ui {
class MenuWidget;
}

class MenuWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MenuWidget(QWidget *parent = 0);
    ~MenuWidget();


signals:
    void newGame();
    void loadGame();
public slots:
    void on_pushButton_newGame_clicked();
    void on_pushButton_loadGame_clicked();
    void on_pushButton_exit_clicked();

    
private:
    Ui::MenuWidget *ui;
};

#endif // MENUWIDGET_H
