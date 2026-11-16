#ifndef WIDGETVALUE_H
#define WIDGETVALUE_H

#include <QWidget>
#include <QString>
#include "rtermo_client.h"

namespace Ui {
class WidgetValue;
}

class WidgetValue : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetValue(QWidget *parent = nullptr);
    ~WidgetValue();

    void setHeadText(QString headText_1, QString headText_2);
    void setValueText(QString valueText_1, QString valueText_2);

    // override
    void setEnabled(bool);
    void setDisabled(bool);

    void updateTemperature();
    void updateSwitchStatus();

    void setClient(RTERMOClient* cli);

private slots:
    void on_pushButton_switch_clicked();

private:
    Ui::WidgetValue *ui;
    QString enabledColorText;
    QString enabledColorText_small;
    QString disabledColorText;
    RTERMOClient* client = nullptr;

private:
    uint8_t powerSwitchEnabled = 0;
};

#endif // WIDGETVALUE_H
