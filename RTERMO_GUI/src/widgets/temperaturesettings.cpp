#include "temperaturesettings.h"
#include "ui_temperaturesettings.h"
#include "settings.h"

TemperatureSettings::TemperatureSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TemperatureSettings)
{
    ui->setupUi(this);
    underlineTitle();
    showAll();
}

TemperatureSettings::~TemperatureSettings()
{
    delete ui;
}

void TemperatureSettings::applySettings()
{
    Settings::set(Settings::Key::dTmax, Settings::Section::Main) =
            ui->lineEdit_dT->text();
}

void TemperatureSettings::underlineTitle()
{
    ui->label_title->font();
    QFont font = ui->label_title->font();
    font.setUnderline(true);
    font.setWeight(QFont::Weight::Normal);
    ui->label_title->setFont(font);
}

void TemperatureSettings::showAll()
{
    ui->lineEdit_dT->setText(
                Settings::get(Settings::Key::dTmax, Settings::Section::Main).toString()
                );

}

void TemperatureSettings::on_lineEdit_dT_editingFinished()
{
    double dT_old = Settings::get(Settings::Key::dTmax, Settings::Section::Main).toDouble();
    bool ok = false;
    double dT_new = ui->lineEdit_dT->text().toDouble(&ok);
    if(!ok || (dT_new <= 0))
    {
        ui->lineEdit_dT->setText(QString::number(dT_old));
    }
}
