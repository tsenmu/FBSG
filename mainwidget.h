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
    void ini();
    void setStartingRound(const int round = 1);
signals:
    void endGame();
    void backToMenu();
private slots:
    void on_pushButton_endGame_clicked();
    void on_pushButton_backToMenu_clicked();
    void on_pushButton_runNextRound_clicked();
    void on_pushButton_restorePreviousRound_clicked();
    void doubleClicked(const QModelIndex& ind);
    void updateUI();
    void on_pushButton_saveReport_clicked();

    void on_tableView_customContextMenuRequested(const QPoint &pos);

private:
    Ui::MainWidget *ui;
    QStandardItemModel* model;
    int startingRound;
};

#endif // MAINWIDGET_H
