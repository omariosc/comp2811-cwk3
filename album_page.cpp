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

  QToolButton *back = new QToolButton();
  back->setProperty("type", "albumButton");
  back->setIcon(QIcon("://back-white"));
  back->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  currentLibrary->addWidget(currentAlbum);
  currentLibrary->addStretch(1);
  currentLibrary->addWidget(back);
  currentLibrary->setSpacing(0);

  // Create the album library, for selecting an album
  AlbumLibrary *albumLibrary = new AlbumLibrary(videos, currentAlbum, toggler);
  toggler->addWidget(albumLibrary);
  albumsPageLayout->setSpacing(0);
  albumsPageLayout->setMargin(0);
  albumLibrary->setLayout(albumsPageLayout);

  QWidget *libraryWidget = new QWidget();
  libraryWidget->setLayout(currentLibrary);
  toggler->addWidget(libraryWidget);

  // Connect button and add to page
  connect(back, &QToolButton::clicked, albumLibrary, &AlbumLibrary::switchBack);
  albumsLayout->addWidget(toggler, 0, 0);
  albumsLayout->setSpacing(0);
  setLayout(albumsLayout);
  show();
}

void AlbumPage::refreshCurrent() { currentAlbum->refresh(); }
