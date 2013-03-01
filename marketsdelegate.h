#ifndef MARKETDELEGATE_H
#define MARKETDELEGATE_H

#include <QItemDelegate>

class MarketsDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MarketsDelegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    
signals:
    
public slots:
    
};

#endif // MARKETDELEGATE_H
