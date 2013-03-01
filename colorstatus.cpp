#include "colorstatus.h"
#include "ui_colorstatus.h"

ColorStatus::ColorStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ColorStatus)
{
    ui->setupUi(this);
    labels.push_back(ui->label_0);
    labels.push_back(ui->label_1);
    labels.push_back(ui->label_2);
}

ColorStatus::~ColorStatus()
{
    delete ui;
}

void ColorStatus::set(int index)
{
    if(index >= 0 && index < labels.size())
    {
        for(int i = 0; i < labels.size(); ++i)
        {
            if(i != index)
            {
                QFont font = labels[i]->font();
                font.setBold(false);
                font.setItalic(false);
                labels[i]->setFont(font);
            }
            else
            {
                QFont font = labels[i]->font();
                font.setBold(true);
                font.setItalic(true);
                labels[i]->setFont(font);
            }
        }
    }
}
