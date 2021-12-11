#include "main_window.h"

#include "mainPage/navigation_button.h"
#include "mainPage/title_label.h"

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

MainWindow::MainWindow(std::vector<VideoFile> &videos) : QWidget(){
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


    QGridLayout *headerLayout = new QGridLayout();
    headerLayout->setMargin(0);
    headerLayout->setSpacing(0);
    headerLayout->addWidget(libraryPageButton, 0, 0);
    headerLayout->addWidget(currentPageLabel, 0, 1, 1, 2);
    headerLayout->addWidget(settingsButton, 0, 3);

    LibraryPage *libraryPage = new LibraryPage(videos);
    FavouritePage *favouritesPage = new FavouritePage(videos);
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



    QHBoxLayout *navTabsLayout = new QHBoxLayout();
    navTabsLayout->setMargin(0);
    navTabsLayout->setSpacing(0);
    navTabsLayout->addWidget(favouritesPageButton);
    navTabsLayout->addWidget(mapPageButton);
    navTabsLayout->addWidget(albumsPageButton);
    navTabsLayout->addWidget(filterPageButton);


    QVBoxLayout *baseLayout = new QVBoxLayout();
    baseLayout->setMargin(0);
    baseLayout->setSpacing(0);
    QWidget * header = new QWidget();
    header->setProperty("type", "menuBackground");
    header->setLayout(headerLayout);
    QWidget * navTabs = new QWidget();
    navTabs->setLayout(navTabsLayout);
    navTabs->setProperty("type", "menuBackground");

    baseLayout->addWidget(header);
    baseLayout->addWidget(stackedPage);
    baseLayout->addWidget(navTabs);

    stackedPage->setCurrentIndex(0);
    libraryPageButton->setActive(true);

    setLayout(baseLayout);
    setWindowTitle("tomeo");
    setMinimumSize(320, 568);


    QFile File(":/tomeoStyleSheet");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    setStyleSheet(StyleSheet);

    //setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // showtime!
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
    qDebug() << "boop";
    SettingsPage settings;
}

