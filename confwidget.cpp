#include "confwidget.h"
#include "ui_confwidget.h"
#include "coordinator.h"
#include "config.h"
#include <QDebug>
#include <QMessageBox>

ConfWidget::ConfWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfWidget)
{
    ui->setupUi(this);
    ui->widget_setOfMarkets->
            setVar("market", "Market", "markets", "Markets", 0x7fffffff);
    ini();
}

ConfWidget::~ConfWidget()
{
    delete ui;
}

void ConfWidget::ini()
{
    Coordinator& coord = Coordinator::getCoordinator();
    coord.loadCurrentConf();
    loadFromConf();
}

void ConfWidget::on_pushButton_back_clicked()
{
    if(changed())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Factory Business Simulator");
        msgBox.setText("The configuration has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Save:
            saveToConf();
            emit back();
            break;
        case QMessageBox::Discard:
            emit back();
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    else
    {
        emit back();
    }
}

void ConfWidget::on_pushButton_apply_clicked()
{
    if(changed())
    {
        saveToConf();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Factory Business Simulator");
        msgBox.setText("The configuration has been applied successfully.");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Factory Business Simulator");
        msgBox.setText("There is no change.");
        msgBox.exec();
    }
}

void ConfWidget::on_pushButton_default_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Factory Business Simulator");
    msgBox.setText("Do you want to restore the default configuration?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret = msgBox.exec();
    if(QMessageBox::Ok == ret)
    {
        Coordinator& coord = Coordinator::getCoordinator();
        coord.loadDefaultConf();
        loadFromConf();
        coord.loadCurrentConf();
        saveToConf();
    }
}

void ConfWidget::loadFromConf()
{
    Config& conf = Config::getConfig();

    ui->doubleSpinBox_interestPerQuarter->setValue(conf.get("Interest per quarter").toDouble());
    ui->doubleSpinBox_penetration->setValue(conf.get("Penetration").toDouble());
    ui->spinBox_addingAgentCost->setValue(conf.get("Adding agent cost").toInt());
    ui->spinBox_balanceUpperLimitToHaveBankLoan->setValue(conf.get("Balance upper limit to have bank loans").toInt());
    ui->spinBox_bankLoanUpperLimitWhileNegativeBalance->setValue(conf.get("Bank loan upper limit while negative balance").toInt());
    ui->spinBox_bankLoanUpperLimitWhilePositiveBalance->setValue(conf.get("Bank loan upper limit while positive balance").toInt());
    ui->spinBox_componentsInAProduct->setValue(conf.get("Components in a product").toInt());
    ui->spinBox_componentStorageCostPerQuarter->setValue(conf.get("Component storage cost per quarter").toInt());
    ui->spinBox_consultantCostPer30Minutes->setValue(conf.get("Consultant cost per 30 minutes").toInt());
    ui->spinBox_daysInAMonth->setValue(conf.get("Days in a month").toInt());
    ui->spinBox_engineersInAProduct->setValue(conf.get("Engineers in a product").toInt());
    ui->spinBox_hoursForATeamInAProduct->setValue(conf.get("Hours in a product").toInt());
    ui->spinBox_hoursInAComponent->setValue(conf.get("Hours in a component").toInt());
    ui->spinBox_initialCash->setValue(conf.get("Initial cash").toInt());
    ui->spinBox_marketPopulation->setValue(conf.get("Market population").toInt());
    ui->spinBox_marketReportCostPerMarketQuarter->setValue(conf.get("Market report cost per market quarter").toInt());
    ui->spinBox_materialCostPerComponent->setValue(conf.get("Material cost per component").toInt());
    ui->spinBox_materialCostPerProduct->setValue(conf.get("Material cost per product").toInt());
    ui->spinBox_monthInAQuarter->setValue(conf.get("Month in a quarter").toInt());
    ui->spinBox_productPriceMinimum->setValue(conf.get("Product price minimum").toInt());
    ui->spinBox_productPriceMaximum->setValue(conf.get("Product price maximum").toInt());
    ui->spinBox_workingHoursInAMonth->setValue(conf.get("Working hours in a month").toInt());
    ui->spinBox_workersInAComponent->setValue(conf.get("Workers in a component").toInt());
    ui->spinBox_salaryMinimum->setValue(conf.get("Salary minimum").toInt());
    ui->spinBox_salaryMaximum->setValue(conf.get("Salary maximum").toInt());
    ui->spinBox_removingAgentCost->setValue(conf.get("Removing agent cost").toInt());
    ui->spinBox_productStorageCostPerQuarter->setValue(conf.get("Products storage cost per quarter").toInt());
    ui->widget_setOfMarkets->setItems(conf.getSetOfMarkets());
}

void ConfWidget::saveToConf()
{
    Coordinator& coord = Coordinator::getCoordinator();
    Config& conf = Config::getConfig();
    conf.set("Interest per quarter", QString::number(ui->doubleSpinBox_interestPerQuarter->value()));
    conf.set("Penetration", QString::number(ui->doubleSpinBox_penetration->value()));
    conf.set("Adding agent cost", QString::number(ui->spinBox_addingAgentCost->value()));
    conf.set("Balance upper limit to have bank loans", QString::number(ui->spinBox_balanceUpperLimitToHaveBankLoan->value()));
    conf.set("Bank loan upper limit while negative balance", QString::number(ui->spinBox_bankLoanUpperLimitWhileNegativeBalance->value()));
    conf.set("Bank loan upper limit while positive balance", QString::number(ui->spinBox_bankLoanUpperLimitWhilePositiveBalance->value()));
    conf.set("Components in a product", QString::number(ui->spinBox_componentsInAProduct->value()));
    conf.set("Component storage cost per quarter", QString::number(ui->spinBox_componentStorageCostPerQuarter->value()));
    conf.set("Consultant cost per 30 minutes", QString::number(ui->spinBox_consultantCostPer30Minutes->value()));
    conf.set("Days in a month", QString::number(ui->spinBox_daysInAMonth->value()));
    conf.set("Engineers in a product", QString::number(ui->spinBox_engineersInAProduct->value()));
    conf.set("Hours in a product", QString::number(ui->spinBox_hoursForATeamInAProduct->value()));
    conf.set("Hours in a component", QString::number(ui->spinBox_hoursInAComponent->value()));
    conf.set("Initial cash", QString::number(ui->spinBox_initialCash->value()));
    conf.set("Market population", QString::number(ui->spinBox_marketPopulation->value()));
    conf.set("Market report cost per market quarter", QString::number(ui->spinBox_marketReportCostPerMarketQuarter->value()));
    conf.set("Material cost per component", QString::number(ui->spinBox_materialCostPerComponent->value()));
    conf.set("Material cost per product", QString::number(ui->spinBox_materialCostPerProduct->value()));
    conf.set("Month in a quarter", QString::number(ui->spinBox_monthInAQuarter->value()));
    conf.set("Product price minimum", QString::number(ui->spinBox_productPriceMinimum->value()));
    conf.set("Product price maximum", QString::number(ui->spinBox_productPriceMaximum->value()));
    conf.set("Working hours in a month", QString::number(ui->spinBox_workingHoursInAMonth->value()));
    conf.set("Workers in a component", QString::number(ui->spinBox_workersInAComponent->value()));
    conf.set("Salary minimum", QString::number(ui->spinBox_salaryMinimum->value()));
    conf.set("Salary maximum", QString::number(ui->spinBox_salaryMaximum->value()));
    conf.set("Removing agent cost", QString::number(ui->spinBox_removingAgentCost->value()));
    conf.set("Products storage cost per quarter", QString::number(ui->spinBox_productStorageCostPerQuarter->value()));
    conf.setSetOfMarkets(ui->widget_setOfMarkets->items());
    coord.saveCurrentConf();
}



bool ConfWidget::changed()
{
    Config& conf = Config::getConfig();
    bool marketEq = true;
    QStringList market1 = conf.getSetOfMarkets();
    QStringList market2 = ui->widget_setOfMarkets->items();
    if(market1.size() != market2.size())
    {
        marketEq = false;
    }
    else
    {
        int size = market1.size();
        for(int i = 0; i < size; ++i)
        {
            if(market1.at(i) != market2.at(i))
            {
                marketEq = false;
                break;
            }
        }
    }

    return !(marketEq && conf.get("Interest per quarter").toDouble() == ui->doubleSpinBox_interestPerQuarter->value() &&
            conf.get("Penetration").toDouble() == ui->doubleSpinBox_penetration->value() &&
            conf.get("Adding agent cost").toInt() == ui->spinBox_addingAgentCost->value() &&
            conf.get("Balance upper limit to have bank loans").toInt() ==  ui->spinBox_balanceUpperLimitToHaveBankLoan->value() &&
            conf.get("Bank loan upper limit while negative balance").toInt() == ui->spinBox_bankLoanUpperLimitWhileNegativeBalance->value() &&
            conf.get("Bank loan upper limit while positive balance").toInt() == ui->spinBox_bankLoanUpperLimitWhilePositiveBalance->value() &&
            conf.get("Components in a product").toInt() == ui->spinBox_componentsInAProduct->value() &&
            conf.get("Component storage cost per quarter").toInt() == ui->spinBox_componentStorageCostPerQuarter->value() &&
            conf.get("Consultant cost per 30 minutes").toInt() == ui->spinBox_consultantCostPer30Minutes->value() &&
            conf.get("Days in a month").toInt() == ui->spinBox_daysInAMonth->value() &&
            conf.get("Engineers in a product").toInt() == ui->spinBox_engineersInAProduct->value() &&
            conf.get("Hours for a team in a product").toInt() == ui->spinBox_hoursForATeamInAProduct->value() &&
            conf.get("Hours in a component").toInt() == ui->spinBox_hoursInAComponent->value() &&
            conf.get("Initial cash").toInt() == ui->spinBox_initialCash->value() &&
            conf.get("Market population").toInt() == ui->spinBox_marketPopulation->value() &&
            conf.get("Market report cost per market quarter").toInt() == ui->spinBox_marketReportCostPerMarketQuarter->value() &&
            conf.get("Material cost per component").toInt() == ui->spinBox_materialCostPerComponent->value() &&
            conf.get("Material cost per product").toInt() == ui->spinBox_materialCostPerProduct->value() &&
            conf.get("Month in a quarter").toInt() == ui->spinBox_monthInAQuarter->value() &&
            conf.get("Product price minimum").toInt() == ui->spinBox_productPriceMinimum->value() &&
            conf.get("Product price maximum").toInt() == ui->spinBox_productPriceMaximum->value() &&
            conf.get("Working hours in a month").toInt() == ui->spinBox_workingHoursInAMonth->value() &&
            conf.get("Workers in a component").toInt() == ui->spinBox_workersInAComponent->value() &&
            conf.get("Salary minimum").toInt() == ui->spinBox_salaryMinimum->value() &&
            conf.get("Salary maximum").toInt() == ui->spinBox_salaryMaximum->value() &&
            conf.get("Removing agent cost").toInt() == ui->spinBox_removingAgentCost->value() &&
            conf.get("Products storage cost per quarter").toInt() == ui->spinBox_productStorageCostPerQuarter->value());
}

