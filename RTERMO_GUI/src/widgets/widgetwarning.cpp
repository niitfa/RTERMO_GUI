#include "widgetwarning.h"
#include "ui_widgetwarning.h"
#include "settings.h"
#include <QIcon>

WidgetWarning::WidgetWarning(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetWarning)
{
    ui->setupUi(this);
    setupWarningText();
    setupIcon();
    setupTimer();
    hideAll();
}

WidgetWarning::~WidgetWarning()
{
    delete ui;
}

void WidgetWarning::setClient(RTERMOClient *cli)
{
    client = cli;
}

void WidgetWarning::setEnabled(bool enabled)
{
    QWidget::setEnabled(enabled);
    if(enabled)
    {
        // ENABLED
        timer.start();
    }
    else
    {
        // DISABLED
        timer.stop();
        hideAll();
    }
}

void WidgetWarning::setDisabled(bool disabled)
{
    WidgetWarning::setEnabled(!disabled);
}

void WidgetWarning::setupWarningText()
{
    // font
    font.setFamily("Inter");
    font.setPixelSize(15);
    font.setWeight(60);
    QString warningColorText = "color: rgb(150,60,60);";

    // label
    ui->label_text->setFont(font);
    ui->label_text->setStyleSheet("border-width:0px;" + warningColorText);
    ui->label_text->setText("Расхождение показаний \nтермометров!");

    // retain size when hidden
    QSizePolicy sp_retain = ui->label_text->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_text->setSizePolicy(sp_retain);

    // multi string
    //ui->label_text->setWordWrap(true);
}

void WidgetWarning::setupIcon()
{
    // icon
    int warningIconSize = 23;
    QIcon warningIcon(":/img/icon_warning.png");
    ui->label_icon->clear();
    ui->label_icon->setPixmap(warningIcon.pixmap(warningIconSize,warningIconSize));

    // retain size when hidden
    QSizePolicy sp_retain = ui->label_icon->sizePolicy();
    sp_retain.setRetainSizeWhenHidden(true);
    ui->label_icon->setSizePolicy(sp_retain);
}

void WidgetWarning::setupTimer()
{
    timer.setSingleShot(false);
    timer.setInterval(500);
    QObject::connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

void WidgetWarning::hideAll()
{
    ui->label_icon->hide();
    ui->label_text->hide();
}

bool WidgetWarning::equalTemperatures()
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

void WidgetWarning::update()
{
    if(equalTemperatures())
    {
        hideAll();
    }
    else
    {
        ui->label_text->show();
        ui->label_icon->setHidden(!ui->label_icon->isHidden());
    }
}
