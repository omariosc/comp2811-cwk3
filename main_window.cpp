#include "main_window.h"

#include "mainPage/navigation_button.h"
#include "mainPage/title_label.h"
#include "mainPage/menulayout.h"

#include <QApplication>
#include <QFile>
#include <QStyle>

#include <QtWidgets/QToolButton>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>

#include "library_page.h"
#include "favourite_page.h"
#include "map_page.h"
#include "album_page.h"
#include "filter_page.h"
#include "settingspage.h"

#include <QDebug>

MainWindow::MainWindow(std::vector<VideoFile> &videos,QStackedWidget* parent, Player* player) : QWidget(){
    stackedParent = parent;
    NavigationButton *libraryPageButton = new NavigationButton("LIBRARY");
    libraryPageButton->setIcon(QIcon(":/libraryIcon"));
    libraryPageButton->setPageNum(0);
    navButtons.push_back(libraryPageButton);
    connect(libraryPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    TitleLabel *currentPageLabel = new TitleLabel();
    currentPageLabel->setText("LIBRARY");
    connect(this, &MainWindow::changedName, currentPageLabel, &TitleLabel::setText);

    NavigationButton *settingsButton = new NavigationButton("SETTINGS");
    settingsButton->setIcon(QIcon(":/settingsIcon"));
    connect(settingsButton, &NavigationButton::clicked, this, &MainWindow::settingsButtonClicked);


    MenuLayout *headerLayout = new MenuLayout();
    headerLayout->addWidget(libraryPageButton, 0, 0);
    headerLayout->addWidget(currentPageLabel, 0, 1, 1, 2);
    headerLayout->addWidget(settingsButton, 0, 3);
    QWidget * header = new QWidget();
    header->setLayout(headerLayout);
    header->setProperty("type", "menuBackground");

    LibraryPage *libraryPage = new LibraryPage(videos,player);
    FavouritePage *favouritesPage = new FavouritePage(videos,player);
    MapPage *mapPage = new MapPage(videos);
    AlbumPage *albumsPage = new AlbumPage(videos);
    FilterPage *filterPage = new FilterPage(videos);

    QStackedWidget *stackedPage = new QStackedWidget();
    stackedPage->addWidget(libraryPage);
    stackedPage->addWidget(favouritesPage);
    stackedPage->addWidget(mapPage);
    stackedPage->addWidget(albumsPage);
    stackedPage->addWidget(filterPage);

    connect(this, &MainWindow::changedFocus, stackedPage, &QStackedWidget::setCurrentIndex);

    NavigationButton *favouritesPageButton = new NavigationButton("FAVOURITES");
    favouritesPageButton->setIcon(QIcon(":/favouritesIcon"));
    favouritesPageButton->setPageNum(1);
    navButtons.push_back(favouritesPageButton);
    connect(favouritesPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *mapPageButton = new NavigationButton("MAP");
    mapPageButton->setIcon(QIcon(":/mapIcon"));
    mapPageButton->setPageNum(2);
    navButtons.push_back(mapPageButton);
    connect(mapPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *albumsPageButton = new NavigationButton("ALBUMS");
    albumsPageButton->setIcon(QIcon(":/albumsIcon"));
    albumsPageButton->setPageNum(3);
    navButtons.push_back(albumsPageButton);
    connect(albumsPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *filterPageButton = new NavigationButton("FILTER");
    filterPageButton->setIcon(QIcon(":/filterIcon"));
    filterPageButton->setPageNum(4);
    navButtons.push_back(filterPageButton);
    connect(filterPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);



    MenuLayout *navTabsLayout = new MenuLayout();
    navTabsLayout->addWidget(favouritesPageButton);
    navTabsLayout->addWidget(mapPageButton);
    navTabsLayout->addWidget(albumsPageButton);
    navTabsLayout->addWidget(filterPageButton);

    QWidget * navTabs = new QWidget();
    navTabs->setLayout(navTabsLayout);
    navTabs->setProperty("type", "menuBackground");

    QVBoxLayout *baseLayout = new QVBoxLayout();
    baseLayout->setMargin(0);
    baseLayout->setSpacing(0);
    baseLayout->addWidget(header);
    baseLayout->addWidget(stackedPage);
    baseLayout->addWidget(navTabs);

    stackedPage->setCurrentIndex(0);
    libraryPageButton->setActive(true);

    setLayout(baseLayout);

    show();
}

void MainWindow::navButtonClicked(int pageNumber, QString pageName){
    emit changedFocus(pageNumber);
    emit changedName(pageName);
    for (NavigationButton* button : navButtons ) {
        button->setActive(false);
    }
    navButtons.at(pageNumber)->setActive(true);
}


void MainWindow::settingsButtonClicked(){
    stackedParent->setCurrentIndex(2);
}

