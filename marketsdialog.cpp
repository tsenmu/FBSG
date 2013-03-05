#include "marketsdialog.h"
#include "ui_marketsdialog.h"
#include "config.h"
#include "coordinator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QLabel>
#include <QSignalMapper>
#include <QDebug>
#include <QMessageBox>

MarketsDialog::MarketsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarketsDialog)
{
    ui->setupUi(this);
    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadRunningConf();
    Config& config = Config::getConfig();
    setOfMarket = config.getSetOfMarkets();
    players = config.getPlayers();
    QVBoxLayout* layout = new QVBoxLayout();
    ui->scrollArea->setLayout(layout);
    foreach(QString player, players)
    {
        QHBoxLayout* hlayout = new QHBoxLayout();
        layout->addLayout(hlayout);
        QLabel* label = new QLabel(player);
        QComboBox* comboBox = new QComboBox();
        comboBox->addItem("");
        foreach(QString market, setOfMarket)
        {
            comboBox->addItem(market);
        }
        currentMarket[comboBox] = "";
        hlayout->addWidget(label);
        hlayout->addWidget(comboBox);
        comboBoxes.append(comboBox);
    }
    mapper = new QSignalMapper(this);

    for(int i = 0; i < comboBoxes.length(); ++i)
    {
        QComboBox* comboBox = comboBoxes[i];
        connect(comboBox, SIGNAL(currentIndexChanged(QString)), mapper, SLOT(map()));
        mapper->setMapping(comboBox, i);
    }
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(updateComboBoxes(int)));
}

MarketsDialog::~MarketsDialog()
{
    delete ui;
}

void MarketsDialog::updateComboBoxes(const int index)
{
    QComboBox* cb = comboBoxes[index];
    QString selectedText = cb->currentText();
    QString releasedText = currentMarket[cb];
    if(selectedText == releasedText) return;
    currentMarket[cb] = selectedText;

    if(!selectedText.isEmpty())
    {
        foreach(QComboBox* comboBox, comboBoxes)
        {
            if(comboBox == cb) continue;
            for(int i = 0; i < comboBox->count(); ++i)
            {
                if(comboBox->itemText(i) == selectedText)
                {
                    comboBox->removeItem(i);
                    break;
                }
            }
        }
    }

    if(!releasedText.isEmpty())
    {
        foreach(QComboBox* comboBox, comboBoxes)
        {
            bool found = false;
            for(int i = 0; i < comboBox->count(); ++i)
            {
                if(comboBox->itemText(i) == releasedText)
                {
                    found = true;
                    break;
                }
            }
            if(!found)
            {
                comboBox->addItem(releasedText);
            }
        }
    }
}

void MarketsDialog::on_pushButton_go_clicked()
{
    bool hasEmpty = false;
    foreach(QComboBox* comboBox, comboBoxes)
    {
        if(comboBox->currentText().isEmpty())
        {
            hasEmpty = true;
            break;
        }
    }
    if(hasEmpty)
    {
        QMessageBox::warning(this, "Warning", "Not all players are assigned with a market");
        return;
    }

    Config& config = Config::getConfig();
    QStringList list;
    foreach(QComboBox* comboBox, comboBoxes)
    {
        list << comboBox->currentText();
    }
    config.setMarkets(list);
    this->accept();
}

void MarketsDialog::on_pushButton_back_clicked()
{
    Config& config = Config::getConfig();
    config.setMarkets(QStringList());
    this->reject();
}

void MarketsDialog::on_pushButton_default_clicked()
{
    foreach(QComboBox* comboBox, comboBoxes)
    {
        comboBox->setCurrentIndex(0);
    }
    foreach(QComboBox* comboBox, comboBoxes)
    {
        comboBox->setCurrentIndex(1);
    }
}
