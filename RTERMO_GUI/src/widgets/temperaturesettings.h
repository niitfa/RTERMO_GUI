#ifndef TEMPERATURESETTINGS_H
#define TEMPERATURESETTINGS_H

#include <QWidget>

namespace Ui {
class TemperatureSettings;
}

class TemperatureSettings : public QWidget
{
    Q_OBJECT

public:
    explicit TemperatureSettings(QWidget *parent = nullptr);
    ~TemperatureSettings();
    void applySettings();
private slots:
    void on_lineEdit_dT_editingFinished();

private:
    void underlineTitle();
    void showAll();
private:
    Ui::TemperatureSettings *ui;
};

#endif // TEMPERATURESETTINGS_H
