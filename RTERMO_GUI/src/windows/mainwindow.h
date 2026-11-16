#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "settingswindow.h"
#include "rtermo_client.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_settings_clicked();
    void updateWindow();

private:
    void setupSettingsButton();
    void setupClient();
    void setupConnectWidget();
    void setupTemperatureWidget();
    void setupTimer();

    void enableMainWindow();
    void disableMainWindow();
private:
    Ui::MainWindow *ui;
    RTERMOClient* client = nullptr;
    SettingsWindow* settingsWindow = new SettingsWindow(this);
    QTimer* timer = new QTimer();
    int currentMsgNum = 0;
    int interval_ms = 10;
};

#endif // MAINWINDOW_H
