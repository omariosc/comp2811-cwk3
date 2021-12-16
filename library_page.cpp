#include "library_page.h"

#include <QGridLayout>
#include <QSize>
#include <QVideoWidget>

#include "player.h"

LibraryPage::LibraryPage(std::vector<VideoFile *> &videos, Player *player)
    : QWidget() {
  library = new VideoLibrary(videos, player);
  QGridLayout *libraryLayout = new QGridLayout();
  libraryLayout->addWidget(library, 0, 0);
  setLayout(libraryLayout);
}

void LibraryPage::refresh() { library->refresh(); }
