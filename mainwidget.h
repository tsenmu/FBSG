#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
class Coordinator;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void on_pushButton_endGame_clicked();
    void on_pushButton_backToMenu_clicked();
signals:
    void endGame();
    void backToMenu();
    
private:
    Ui::MainWidget *ui;
};

#endif // MAINWIDGET_H
