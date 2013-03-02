#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QWidget>

namespace Ui {
class StartWidget;
}

class QStandardItemModel;
class StartWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit StartWidget(QWidget *parent = 0);
    ~StartWidget();
    void ini();

signals:
    void startGame();
    void backToMenu();

public slots:
    void on_pushButton_backToMenu_clicked();
    void on_pushButton_startGame_clicked();
    void on_pushButton_markets_clicked();
    void reachLimit_emitted();
    void itemChanged_emitted();
    
private:
    Ui::StartWidget *ui;

};

#endif // STARTWIDGET_H
