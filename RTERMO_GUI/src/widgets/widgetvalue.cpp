#include "widgetvalue.h"
#include "ui_widgetvalue.h"
#include "settings.h"

WidgetValue::WidgetValue(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetValue)
{
    ui->setupUi(this);

    setValueText("0", "0");
    setHeadText("Description 1", "Description 2");
    
    QFont headFont;
    headFont.setFamily("Inter");
    headFont.setPixelSize(16);
    headFont.setWeight(55);

    QFont valueFont;
    valueFont.setFamily("Inter");
    valueFont.setPixelSize(25); // 28
    valueFont.setWeight(60);

    // border
    ui->frame_border->setStyleSheet(
                //" QFrame { background-color: white; } "
                " QFrame { background-color: rgb(247,247,247); } "
                " QFrame { border-radius:10px; }"
                " QFrame { border-style: outset; }"
                " QFrame { border-width:1px; }"
                " QFrame { border-color:rgb(180,180,180); }"
                // disabled
                " QFrame:disabled { background-color: rgb(247,247,247); } "
                );

    ui->verticalLayout_border->setParent(nullptr);
    ui->frame_border->setLayout(ui->verticalLayout_border);

    this->enabledColorText =  "color: rgb(50,70,100);";
    this->enabledColorText_small_equal = "color: rgb(150,170,190);";
    this->enabledColorText_small_error = "color: rgb(150,60,60);";
    this->enabledColorText_small = this->enabledColorText_small_equal;
    this->disabledColorText = "color: rgb(130,130,130);";

    // head text
    ui->label_head1->setFont(headFont);
    // value text
    ui->label_value1->setFont(valueFont);

    headFont.setPixelSize(headFont.pixelSize() - 2);
    valueFont.setPixelSize(valueFont.pixelSize() - 2);
    // head text 2
    ui->label_head2->setFont(headFont);
    // value text 2
    ui->label_value2->setFont(valueFont);
    // head rscan dose text
    ui->label_enable->setFont(headFont);

    ui->label_icon->setText("");
    ui->pushButton_switch->setText("");
    // init style
    this->WidgetValue::setEnabled(false);
}

WidgetValue::~WidgetValue()
{
    delete ui;
}

void WidgetValue::setHeadText(QString headText_1, QString headText_2)
{
    ui->label_head1->setText(headText_1);
    ui->label_head2->setText(headText_2);
}

void WidgetValue::setValueText(QString valueText_1, QString valueText_2)
{
    ui->label_value1->setText(valueText_1);
    ui->label_value2->setText(valueText_2);
}

void WidgetValue::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if(enabled)
    {
        ui->label_head1->setStyleSheet("border-width:0px;" + this->enabledColorText);
        ui->label_value1->setStyleSheet("border-width:0px;" + this->enabledColorText);
        ui->label_head2->setStyleSheet("border-width:0px;" + this->enabledColorText_small);
        ui->label_value2->setStyleSheet("border-width:0px;" + this->enabledColorText_small);
        ui->label_enable->setStyleSheet("border-width:0px;" + this->enabledColorText);
        ui->label_icon->setStyleSheet("border-width:0px;" + this->enabledColorText);
    }
    else
    {
        ui->label_head1->setStyleSheet("border-width:0px;" +this->disabledColorText);
        ui->label_value1->setStyleSheet("border-width:0px;" + this->disabledColorText);
        ui->label_head2->setStyleSheet("border-width:0px;" + this->disabledColorText);
        ui->label_value2->setStyleSheet("border-width:0px;" + this->disabledColorText);
        ui->label_enable->setStyleSheet("border-width:0px;" +this->disabledColorText);
        ui->label_icon->setStyleSheet("border-width:0px;" +this->disabledColorText);
    }
}
void WidgetValue::setDisabled(bool disabled)
{
    this->WidgetValue::setEnabled(!disabled);
}

void WidgetValue::updateTemperature()
{
    if(client)
    {
        double t1 = static_cast<double>(client->getTempA()) / 1000.;
        double t2 = static_cast<double>(client->getTempB()) / 1000.;
        ui->label_value1->setText( QString::number(t1, 'f', 1) + " ℃" );
        ui->label_value2->setText( QString::number(t2, 'f', 1) + " ℃" );
        if(equalTemperatures())
        {
            ui->label_value2->setStyleSheet("border-width:0px;" + this->enabledColorText_small_equal);
        }
        else
        {
            ui->label_value2->setStyleSheet("border-width:0px;" + this->enabledColorText_small_error);
        }
    }
}

void WidgetValue::updateSwitchStatus()
{
    if(client)
    {
        uint8_t enabled = client->getRDOSEStatus();
        if(enabled != powerSwitchEnabled)
        {
            powerSwitchEnabled = enabled;
            bool checked = false;
            enabled ? (checked = true) : (checked = false);
            ui->pushButton_switch->setChecked(checked);
        }
    }
}

void WidgetValue::setClient(RTERMOClient *cli)
{
    client = cli;
}

bool WidgetValue::equalTemperatures()
{
    bool equal = true;
    if(client)
    {
        int dT_max = Settings::get(Settings::Key::dTmax, Settings::Section::Main).toDouble() * 1000;
        int dT = qAbs(client->getTempA() - client->getTempB());
        equal = (dT < dT_max);
    }
    return equal;
}

void WidgetValue::on_pushButton_switch_clicked()
{
    if(ui->pushButton_switch->isChecked())
    {
        if(client)
        {
            client->enableRDOSE();
        }
    }
    else
    {
        if(client)
        {
            client->disableRDOSE();
        }
    }
}
