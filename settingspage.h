#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QDialog>

class SettingsPage : public QDialog {
    Q_OBJECT
public:
    SettingsPage(QWidget *parent = nullptr);

private slots:
    void returnBack();
};

#endif // SETTINGSPAGE_H
