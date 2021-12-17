#include "album_page.h"

#include <albumsPage/albumlibrary.h>

#include <QGridLayout>
#include <QLabel>
#include <QSize>
#include <QVideoWidget>

#include "favourite_page.h"
#include "libraryPage/videolibrary.h"

AlbumPage::AlbumPage(std::vector<VideoFile *> &videos, Player *videoPlayer)
    : QWidget(), player(videoPlayer), videos(videos) {
  toggler = new QStackedWidget;
  // Create the layouts
  QGridLayout *albumsLayout = new QGridLayout();
  QVBoxLayout *currentLibrary = new QVBoxLayout();
  QVBoxLayout *albumsPageLayout = new QVBoxLayout();

  // Create the current album browser. Which is a VideoLibrary + Back button
  currentAlbum = new VideoLibrary(videos, player);

  //Create the back button to return to the AlbumLibrary
  QToolButton *back = new QToolButton();
  back->setProperty("type", "albumButton");
  back->setIcon(QIcon("://back-white"));
  back->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);

  //Add all the widgets for browsing the selected album to the layout
  currentLibrary->addWidget(currentAlbum);
  currentLibrary->addStretch(1);
  currentLibrary->addWidget(back);
  currentLibrary->setSpacing(0);
  currentLibrary->setMargin(0);

  // Create the AlbumLibrary, for selecting an album to browse
  AlbumLibrary *albumLibrary = new AlbumLibrary(videos, currentAlbum, toggler);
  toggler->addWidget(albumLibrary);
  albumsPageLayout->setSpacing(0);
  albumsPageLayout->setMargin(0);
  albumLibrary->setLayout(albumsPageLayout);

  //Add the layout for browsing through the selected album to a widget, then add widget to the QStackedWidget
  QWidget *libraryWidget = new QWidget();
  libraryWidget->setLayout(currentLibrary);
  toggler->addWidget(libraryWidget);

  // Connect back button and the AlbumLibrary to the QStackedWidget
  connect(back, &QToolButton::clicked, albumLibrary, &AlbumLibrary::switchBack);
  albumsLayout->addWidget(toggler, 0, 0);
  albumsLayout->setSpacing(0);
  setLayout(albumsLayout);
}

void AlbumPage::refreshCurrent() { currentAlbum->refresh(); }
