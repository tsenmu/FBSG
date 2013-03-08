#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_action_newGame_triggered();
    void on_action_close_triggered();
    void on_action_loadGame_triggered();
    void on_action_saveGame_triggered();
    void on_action_configuration_triggered();
    void on_pushButton_configuration_clicked();
    void back_emitted();
    void startGame_emitted();
    void endGame_emitted();
    void backToMenu_emitted();
protected:
    void showEvent(QShowEvent * event );
    void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindow *ui;
    int previousIndex;
    void initStackedWidget();
    void switchToPage(int index);
    QHash<QWidget*, int> pageMap;
};

#endif // MAINWINDOW_H
