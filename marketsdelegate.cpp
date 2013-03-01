#include "marketsdelegate.h"
#include <QComboBox>
#include <QLineEdit>

MarketsDelegate::MarketsDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *MarketsDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem & option ,
                                      const QModelIndex & index) const
{
    if(index.column() != 1)
    {
        QLineEdit* editor = new QLineEdit(parent);
        return editor;
    }
    else
    {
        QComboBox* editor = new QComboBox(parent);
        return editor;
    }
}

void MarketsDelegate::setEditorData(QWidget *editor,
                                   const QModelIndex &index) const
{
    if(index.column() != 1)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        lineEdit->setText(value);
    }
    else
    {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        comboBox->setCurrentIndex(value);
    }
}

void MarketsDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                  const QModelIndex &index) const
{
    if(index.column() != 1)
    {
        QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
    else
    {
        QComboBox* comboBox = static_cast<QComboBox*>(editor);
        int ind = comboBox->currentIndex();
        model->setData(index, ind, Qt::EditRole);
    }
}

void MarketsDelegate::updateEditorGeometry(QWidget *editor,
                                          const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
