#ifndef WIDGETWARNING_H
#define WIDGETWARNING_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include "rtermo_client.h"

namespace Ui {
class WidgetWarning;
}

class WidgetWarning : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetWarning(QWidget *parent = nullptr);
    ~WidgetWarning();
    void setClient(RTERMOClient* cli);
    void setEnabled(bool enabled);
    void setDisabled(bool disabled);
private:
    void setupWarningText();
    void setupIcon();
    void setupTimer();
    void hideAll();
    bool equalTemperatures();
private slots:
    void update();

private:
    Ui::WidgetWarning *ui;
    RTERMOClient* client = nullptr;
    QTimer timer;
    QFont font;
};

#endif // WIDGETWARNING_H
