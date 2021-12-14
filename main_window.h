#ifndef THE_MAIN_WINDOW_H
#define THE_MAIN_WINDOW_H

#include <QWidget>
#include <vector>
#include "video_file.h"
#include "mainPage/navigation_button.h"
#include <player.h>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(std::vector<VideoFile> &videos,Player* player);

signals:
    void changedFocus(int pageNumber);
    void changedName(QString name);

private slots:
    void navButtonClicked(int pageNumber, QString pageName);
    void settingsButtonClicked();

private:
    std::vector<NavigationButton*> navButtons;

};

#endif // MAIN_WINDOW_H
