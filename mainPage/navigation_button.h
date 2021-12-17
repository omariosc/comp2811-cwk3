#ifndef THE_NAVIGATION_BUTTON_H
#define THE_NAVIGATION_BUTTON_H

#include <QToolButton>

class NavigationButton : public QToolButton {
  Q_OBJECT

 public:
  NavigationButton(QString newName = "");
  void setName(QString newName);
  void setPageNum(int pageNum);
  void setActive(bool newState);

 signals:
  void clicked(int pageNumber, QString pageName); // Outputs clicked with the number and name for page that is being changed to

 private slots:
  void dataClicked(); // Connects button released with emitting the custom clicked signal

 private:
  QString name;
  int pageNum;
  bool active;
};

#endif  // THE_NAVIGATION_BUTTON_H
