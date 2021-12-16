#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QStackedWidget>
#include <QWidget>

class SettingsPage : public QWidget {
  Q_OBJECT
 public:
  SettingsPage(QStackedWidget* parent);

 private slots:
  void returnBack();

 private:
  QStackedWidget* stackedParent;
};

#endif  // SETTINGSPAGE_H
