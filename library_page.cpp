#include "library_page.h"

#include <QGridLayout>
#include <QSize>
#include <QVideoWidget>

#include "player.h"

LibraryPage::LibraryPage(std::vector<VideoFile *> &videos, Player *player)
    : QWidget() {
  // As a player widget is no longer included on the page, only a VideoLibrary
  // is required. Still better to have it as a seperate page in case more
  // additions are added in the future.
  library = new VideoLibrary(videos, player);
  // Requires layout to display
  QGridLayout *libraryLayout = new QGridLayout();
  libraryLayout->addWidget(library, 0, 0);
  setLayout(libraryLayout);
}

void LibraryPage::refresh() { library->refresh(); }
