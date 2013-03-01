#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>

class QStandardItemModel;
namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit ListWidget(QWidget *parent = 0);
    ~ListWidget();
    void setVar(const QString& itemName,
                const QString& itemNameCap,
                const QString& itemNameP,
                const QString& itemNameCapP,
                int limit);
    QStringList items();
    void setItems(const QStringList& list);
    void setLabelDynamic(const QString& str);
public slots:
    void on_pushButton_add_clicked();
    void on_pushButton_delete_clicked();
    void on_pushButton_batchAdd_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_edit_clicked();
signals:
    void reachLimit();
    
private:
    bool itemExists(const QString& str);
    bool itemIsValid(const QString& str, const QString& exception = "");
    QString genNewItem();
    int parseItemName(const QString& str);
    bool addItem(const QString& str);
    Ui::ListWidget *ui;
    QStandardItemModel* model;
    QString itemName;
    QString itemNameCap;
    QString itemNameP;
    QString itemNameCapP;
    int limit;
};

#endif // LISTWIDGET_H
