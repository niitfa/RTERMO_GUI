#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(400, 270);
    setWindowTitle("RSCAN DOSE (RTERMO)");
    setupSettingsButton();
    setupClient();
    setupConnectWidget();
    setupTemperatureWidget();
    setupTimer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSettingsButton()
{
    QPushButton* button = ui->pushButton_settings;
    button->setText("");
    button->setStyleSheet("* { background-color: rgb(220,220,220) }");

    /* Icon */
    double iconScaleFactor = 0.70;
    QSize size = button->size();
    size.setWidth(static_cast<int>(size.width() * iconScaleFactor));
    size.setHeight(static_cast<int>(size.height() * iconScaleFactor));
    button->setIcon(QIcon(":/img/button_icon_settings.png"));
    button->setIconSize(size);
}

void MainWindow::setupClient()
{
    std::string ip = Settings::get(Settings::Key::IP, Settings::Section::Main).toString().toStdString();
    uint16_t port = static_cast<uint16_t>(Settings::get(Settings::Key::Port, Settings::Section::Main).toInt());

    client = new RTERMOClient(ip, port);
    client->setIP(ip);
    client->setPort(port);
    client->setVerbose(true);
}

void MainWindow::setupConnectWidget()
{
    ui->widget_connect->setTCPClient(this->client);
    std::function<void()> enableCallback(std::bind(&MainWindow::enableMainWindow, this));
    ui->widget_connect->setConnectionEstablishedCallback(enableCallback);
    std::function<void()> disableCallback(std::bind(&MainWindow::disableMainWindow, this));
    ui->widget_connect->setConnectionLostCallback(disableCallback);
    ui->widget_connect->connect();
}

void MainWindow::setupTemperatureWidget()
{
    ui->widget_temperature->setHeadText("Температура в камере:", "Температура (резерв):");
    ui->widget_temperature->setClient(client);
}

void MainWindow::setupTimer()
{
    timer->setSingleShot(false);
    timer->setInterval(this->interval_ms);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
}

void MainWindow::enableMainWindow()
{
    ui->widget_temperature->setEnabled(1);
    timer->start();
}

void MainWindow::disableMainWindow()
{
    ui->widget_temperature->setEnabled(0);
    timer->stop();
}

void MainWindow::on_pushButton_settings_clicked()
{
    if(settingsWindow)
    {
        settingsWindow->show();
    }
}

#include <iostream>
void MainWindow::updateWindow()
{
    int msgNum = 0;
    if(client)
    {
        msgNum = client->getMessageNum();
    }
    if(client && msgNum != currentMsgNum)
    {
        currentMsgNum = msgNum;
        ui->widget_temperature->updateTemperature();
        ui->widget_temperature->updateSwitchStatus();
    }
}
