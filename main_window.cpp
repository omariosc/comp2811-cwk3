#include "main_window.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QStyle>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

#include "album_page.h"
#include "favourite_page.h"
#include "filter_page.h"
#include "library_page.h"
#include "mainPage/menulayout.h"
#include "mainPage/navigation_button.h"
#include "mainPage/title_label.h"
#include "map_page.h"
#include "settingspage.h"

MainWindow::MainWindow(std::vector<VideoFile *> &videos, QStackedWidget *parent,
                       Player *player)
    : QWidget() {
  stackedParent = parent;

  // Create Page Widgets
  LibraryPage *libraryPage = new LibraryPage(videos, player);
  FavouritePage *favouritesPage = new FavouritePage(videos, player);
  MapPage *mapPage = new MapPage(videos, player);
  AlbumPage *albumsPage = new AlbumPage(videos, player);
  FilterPage *filterPage = new FilterPage(videos, player);

  // Add pages to stacked widget
  QStackedWidget *stackedPage = new QStackedWidget();
  stackedPage->addWidget(libraryPage);
  stackedPage->addWidget(favouritesPage);
  stackedPage->addWidget(mapPage);
  stackedPage->addWidget(albumsPage);
  stackedPage->addWidget(filterPage);

  // Sets the current displayed page to be where the navigation button requires
  connect(this, &MainWindow::changedFocus, stackedPage,
          &QStackedWidget::setCurrentIndex);
  // Calls relevant refresh function of all widgets when switching between pages
  connect(this, &MainWindow::refreshLibrary, libraryPage,
          &LibraryPage::refresh);
  connect(this, &MainWindow::refreshLibrary, favouritesPage,
          &FavouritePage::refresh);
  connect(this, &MainWindow::refreshLibrary, mapPage, &MapPage::refresh);
  connect(this, &MainWindow::refreshLibrary, filterPage, &FilterPage::refresh);
  connect(this, &MainWindow::refreshLibrary, albumsPage,
          &AlbumPage::refreshCurrent);

  // Set Initial Title
  TitleLabel *currentPageLabel = new TitleLabel();
  currentPageLabel->setText("LIBRARY");
  connect(this, &MainWindow::changedName, currentPageLabel,
          &TitleLabel::setText);

  // Library Page Button
  NavigationButton *libraryPageButton = new NavigationButton("LIBRARY");
  libraryPageButton->setIcon(QIcon(":/libraryIcon"));
  libraryPageButton->setPageNum(0);
  navButtons.push_back(libraryPageButton);
  connect(libraryPageButton, &NavigationButton::clicked, this,
          &MainWindow::navButtonClicked);

  // Settings Page Button
  NavigationButton *settingsButton = new NavigationButton("SETTINGS");
  settingsButton->setIcon(QIcon(":/settingsIcon"));
  connect(settingsButton, &NavigationButton::clicked, this,
          &MainWindow::settingsButtonClicked);

  // Favourites Page Button
  NavigationButton *favouritesPageButton = new NavigationButton("FAVOURITES");
  favouritesPageButton->setIcon(QIcon(":/favouritesIcon"));
  favouritesPageButton->setPageNum(1);
  navButtons.push_back(favouritesPageButton);
  connect(favouritesPageButton, &NavigationButton::clicked, this,
          &MainWindow::navButtonClicked);

  // Map Page Button
  NavigationButton *mapPageButton = new NavigationButton("MAP");
  mapPageButton->setIcon(QIcon(":/mapIcon"));
  mapPageButton->setPageNum(2);
  navButtons.push_back(mapPageButton);
  connect(mapPageButton, &NavigationButton::clicked, this,
          &MainWindow::navButtonClicked);

  // Albums Page Button
  NavigationButton *albumsPageButton = new NavigationButton("ALBUMS");
  albumsPageButton->setIcon(QIcon(":/albumsIcon"));
  albumsPageButton->setPageNum(3);
  navButtons.push_back(albumsPageButton);
  connect(albumsPageButton, &NavigationButton::clicked, this,
          &MainWindow::navButtonClicked);

  // Filter Page Button
  NavigationButton *filterPageButton = new NavigationButton("FILTER");
  filterPageButton->setIcon(QIcon(":/filterIcon"));
  filterPageButton->setPageNum(4);
  navButtons.push_back(filterPageButton);
  connect(filterPageButton, &NavigationButton::clicked, this,
          &MainWindow::navButtonClicked);

  // Upper Navigation Layout
  MenuLayout *headerLayout = new MenuLayout();
  headerLayout->addWidget(libraryPageButton, 0, 0);
  headerLayout->addWidget(currentPageLabel, 0, 1, 1, 2);
  headerLayout->addWidget(settingsButton, 0, 3);
  QWidget *header = new QWidget();
  header->setLayout(headerLayout);
  header->setProperty("type", "menuBackground");

  // Lower Navigation Layout
  MenuLayout *navTabsLayout = new MenuLayout();
  navTabsLayout->addWidget(favouritesPageButton);
  navTabsLayout->addWidget(mapPageButton);
  navTabsLayout->addWidget(albumsPageButton);
  navTabsLayout->addWidget(filterPageButton);

  QWidget *navTabs = new QWidget();
  navTabs->setLayout(navTabsLayout);
  navTabs->setProperty("type", "menuBackground");

  // Layout of Whole Widget
  QVBoxLayout *baseLayout = new QVBoxLayout();
  baseLayout->setMargin(0);
  baseLayout->setSpacing(0);
  baseLayout->addWidget(header);
  baseLayout->addWidget(stackedPage);
  baseLayout->addWidget(navTabs);

  stackedPage->setCurrentIndex(0);
  libraryPageButton->setActive(true);

  setLayout(baseLayout);
}

void MainWindow::navButtonClicked(int pageNumber, QString pageName) {
  // Emits relevant information to widgets within this class for visual updates
  emit changedFocus(pageNumber);
  emit changedName(pageName);
  for (NavigationButton *button : navButtons) {
    button->setActive(false);
  }
  // Only the current navigation button should be active
  navButtons.at(pageNumber)->setActive(true);
  // Must refresh after page has been switched so that sizeHints work correctly
  emit refreshLibrary();
}

void MainWindow::settingsButtonClicked() { stackedParent->setCurrentIndex(2); }
