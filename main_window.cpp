#include "main_window.h"

#include "mainPage/navigation_button.h"
#include "mainPage/title_label.h"

#include <QApplication>
#include <QFile>

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

MainWindow::MainWindow() : QWidget(){
    NavigationButton *libraryPageButton = new NavigationButton("Library");
    libraryPageButton->setIcon(QIcon(":/libraryIcon"));
    libraryPageButton->setPageNum(0);
    navButtons.push_back(libraryPageButton);
    connect(libraryPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    TitleLabel *currentPageLabel = new TitleLabel();
    currentPageLabel->setText("Favourites");
    connect(this, &MainWindow::changedName, currentPageLabel, &TitleLabel::setText);

    NavigationButton *settingsButton = new NavigationButton("Settings");
    settingsButton->setIcon(QIcon(":/settingsIcon"));


    QGridLayout *headerLayout = new QGridLayout();
    headerLayout->setMargin(0);
    headerLayout->setSpacing(0);
    headerLayout->addWidget(libraryPageButton, 0, 0);
    headerLayout->addWidget(currentPageLabel, 0, 1, 1, 2);
    headerLayout->addWidget(settingsButton, 0, 3);

    LibraryPage *libraryPage = new LibraryPage();
    FavouritePage *favouritesPage = new FavouritePage();
    MapPage *mapPage = new MapPage();
    AlbumPage *albumsPage = new AlbumPage();
    FilterPage *filterPage = new FilterPage();

    QStackedWidget *stackedPage = new QStackedWidget();
    stackedPage->addWidget(libraryPage);
    stackedPage->addWidget(favouritesPage);
    stackedPage->addWidget(mapPage);
    stackedPage->addWidget(albumsPage);
    stackedPage->addWidget(filterPage);

    connect(this, &MainWindow::changedFocus, stackedPage, &QStackedWidget::setCurrentIndex);

    stackedPage->setStyleSheet("background:#000000;");

    NavigationButton *favouritesPageButton = new NavigationButton("Favourites");
    favouritesPageButton->setIcon(QIcon(":/favouritesIcon"));
    favouritesPageButton->setPageNum(1);
    navButtons.push_back(favouritesPageButton);
    connect(favouritesPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *mapPageButton = new NavigationButton("Map");
    mapPageButton->setIcon(QIcon(":/mapIcon"));
    mapPageButton->setPageNum(2);
    navButtons.push_back(mapPageButton);
    connect(mapPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *albumsPageButton = new NavigationButton("Albums");
    albumsPageButton->setIcon(QIcon(":/albumsIcon"));
    albumsPageButton->setPageNum(3);
    navButtons.push_back(albumsPageButton);
    connect(albumsPageButton, &NavigationButton::clicked, this, &MainWindow::navButtonClicked);

    NavigationButton *filterPageButton = new NavigationButton("Filter");
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
    setMinimumSize(800, 680);

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


