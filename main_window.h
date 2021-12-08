#ifndef THE_MAIN_WINDOW_H
#define THE_MAIN_WINDOW_H

#include <QWidget>
#include <vector>
#include "mainPage/navigation_button.h"

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

signals:
    void changedFocus(int pageNumber);
    void changedName(QString name);

private slots:
    void navButtonClicked(int pageNumber, QString pageName);

private:
    std::vector<NavigationButton*> navButtons;

};

#endif // MAIN_WINDOW_H
