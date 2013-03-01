#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QModelIndex>
class Coordinator;

namespace Ui {
class MainWidget;
}

class QStandardItemModel;

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

public slots:
    void on_pushButton_endGame_clicked();
    void on_pushButton_backToMenu_clicked();
    void ini();
    void doubleClicked(const QModelIndex& ind);
signals:
    void endGame();
    void backToMenu();
    
private:
    Ui::MainWidget *ui;
    QStandardItemModel* model;
};

#endif // MAINWIDGET_H
