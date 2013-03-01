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
    explicit DecisionWidget(QHash<QString, QString> *record, int round = 1, QWidget *parent = 0);
    ~DecisionWidget();
    QHash<QString, QString>& getRecord();
    
public slots:
    void spinBoxChanged(int);
private slots:
    void on_hiredConsultant_clicked(bool checked);

private:
    Ui::DecisionWidget *ui;
    QHash<QString, QString> *record;
};

#endif // DECISIONWIDGET_H
