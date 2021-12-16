#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H

#include <QStackedWidget>
#include <QWidget>

class SettingsPage : public QWidget {
  Q_OBJECT
 public:
  SettingsPage(QStackedWidget* parent);

 private slots:
  void returnBack(); // Returns back to index(0) within the stacked widget

 private:
  QStackedWidget* stackedParent; // Saves pointer to parent so that can easily call switch back to main stacked page
};

#endif  // SETTINGSPAGE_H
