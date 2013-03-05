#include "listwidget.h"
#include "ui_listwidget.h"
#include <QStandardItemModel>
#include <QInputDialog>
#include <QMessageBox>
#include <QDebug>

ListWidget::ListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListWidget)
{
    ui->setupUi(this);
    model = new QStandardItemModel(this);
    ui->listView->setModel(model);
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::setVar(const QString &itemName, const QString &itemNameCap,
                   const QString& itemNameP, const QString& itemNameCapP,
                        int limit)
{
    this->itemName = itemName;
    this->itemNameCap = itemNameCap;
    this->itemNameP = itemNameP;
    this->itemNameCapP = itemNameCapP;
    this->limit = limit;
    ui->label->setText(itemNameCapP);
}


void ListWidget::on_pushButton_delete_clicked()
{
    int index = ui->listView->currentIndex().row();
    if(index >= 0 && index < model->rowCount())
    {
        model->removeRow(index);
        if(limit != 0x7fffffff)
        {
            this->setLabelDynamic(QString("%1/%2").arg(model->rowCount()).arg(limit));
        }
    }
    emit itemChanged();
}

void ListWidget::on_pushButton_edit_clicked()
{
    int index = ui->listView->currentIndex().row();
    if(index >= 0 && index < model->rowCount())
    {
        bool ok;
        QString name = QInputDialog::getText(this, QString("Edit %1").arg(itemName),
                                             QString("%1 name").arg(itemNameCap),
                                             QLineEdit::Normal, model->item(index)->text(), &ok);
        if(ok)
        {
            if(itemIsValid(name,  model->item(index)->text()))
            {
                model->item(index)->setText(name);
            }
            else
            {
                QMessageBox::critical(this, "Error", QString("%1 is invalid.").arg(name));
            }
        }
    }
    emit itemChanged();
}

void ListWidget::on_pushButton_batchAdd_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, QString("Batch add new %1").arg(itemNameP),
                                         QString("%1 names (separate names with ';')").arg(itemNameCap),
                                         QLineEdit::Normal, "", &ok);
    if(ok)
    {
        foreach(QString name, text.split(';'))
        {
            if(name.isEmpty())
            {
                continue;
            }

            if(itemIsValid(name))
            {
                if(!addItem(name))
                {
                    return;
                }
            }
            else
            {
                QMessageBox::warning(this, "Warning", QString("%1 is invalid.").arg(name));
            }
        }
    }

}

void ListWidget::on_pushButton_clear_clicked()
{
    model->clear();
    emit itemChanged();
}

void ListWidget::on_pushButton_add_clicked()
{
    bool ok;
    QString text = QInputDialog::getText(this, QString("Add new %1").arg(itemName),
                                         QString("%1 name").arg(itemNameCap) , QLineEdit::Normal,
                                         genNewItem(), &ok);
    if(!ok) return;
    if(itemIsValid(text))
    {
        addItem(text);
    }
    else
    {
        QMessageBox::critical(this, "Error", QString("%1 name is not valid.").arg(itemNameCap));
        return;
    }
}

QString ListWidget::genNewItem()
{
    QSet<int> set;
    for(int i = 0; i < model->rowCount(); ++i)
    {
        QString name = model->item(i)->text();
        int number = parseItemName(name);
        if(number != -1)
        {
            set.insert(number);
        }
    }
    int last = 0;
    int var = 0;
    foreach(int element,set)
    {
        if(element - last != 1)
        {
            var = last + 1;
            break;
        }
        last = element;
    }
    if(var == 0)
    {
        var = last + 1;
    }
    return QString("%1%2").arg(itemNameCap).arg(var);
}

int ListWidget::parseItemName(const QString& str)
{
    QString strc = str;
    if(strc.startsWith(itemNameCap))
    {
        strc.remove(0, 6);
        bool ok;
        int num = strc.toInt(&ok);
        if(ok)
        {
            return num;
        }
    }
    return -1;
}

bool ListWidget::itemIsValid(const QString& str, const QString& exception)
{
    if(!exception.isEmpty())
    {
        if(str == exception)
        {
            return true;
        }
    }
    return !str.contains(';') && !str.isEmpty() && !itemExists(str);
}

bool ListWidget::addItem(const QString& str)
{
    if(model->rowCount() == limit)
    {
        emit reachLimit();
        return false;
    }
    QStandardItem* item = new QStandardItem(str);

    model->appendRow(item);
    if(limit != 0x7fffffff)
    {
        setLabelDynamic(QString("%1/%2").arg(model->rowCount()).arg(limit));
    }
    emit itemChanged();
    return true;
}

bool ListWidget::itemExists(const QString &str)
{
    for(int i = 0; i < model->rowCount(); ++i)
    {
        QString name = model->item(i)->text();
        if(name == str)
        {
            return true;
        }
    }
    return false;
}

QStringList ListWidget::items()
{
    QStringList list;
    int count = model->rowCount();
    for(int i = 0; i < count; ++i)
    {
        list << model->item(i)->text();
    }
    return list;
}

void ListWidget::setItems(const QStringList& list)
{
    model->clear();
    foreach(QString str, list)
    {
        this->addItem(str);
    }

}


void ListWidget::setLabelDynamic(const QString &str)
{
    ui->label_dynamic->setText(str);
}
