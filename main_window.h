#ifndef THE_MAIN_WINDOW_H
#define THE_MAIN_WINDOW_H

#include <player.h>

#include <QStackedWidget>
#include <QWidget>
#include <vector>

#include "mainPage/navigation_button.h"
#include "video_file.h"

class MainWindow : public QWidget {
  Q_OBJECT

 public:
  MainWindow(std::vector<VideoFile*>& videos, QStackedWidget* parent,
             Player* player);

 signals:
  void changedFocus(int pageNumber); // Emits new page number
  void changedName(QString name); // Emits new page name
  void refreshLibrary(); // videoLibrary needs to be refreshed when loading page containing one so that the layout is correct

 private slots:
  void navButtonClicked(int pageNumber, QString pageName); // Emits necessary signals when navigation button is clicked
  void settingsButtonClicked(); // To be called when settings button is clicked

 private:
  std::vector<NavigationButton*> navButtons;
  QStackedWidget* stackedParent;
};

#endif  // MAIN_WINDOW_H
