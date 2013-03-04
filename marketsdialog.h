#ifndef MARKETSDIALOG_H
#define MARKETSDIALOG_H

#include <QDialog>
#include <QHash>
class QComboBox;


namespace Ui {
class MarketsDialog;
}
class QSignalMapper;

class MarketsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit MarketsDialog(QWidget *parent = 0);
    ~MarketsDialog();
public slots:
    void updateComboBoxes(const int);
    void on_pushButton_go_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_default_clicked();
private:
    Ui::MarketsDialog *ui;
    QStringList setOfMarket;
    QStringList players;
    QList<QComboBox*> comboBoxes;
    QSignalMapper* mapper;
    QHash<QComboBox*, QString> currentMarket;
};

#endif // MARKETSDIALOG_H
