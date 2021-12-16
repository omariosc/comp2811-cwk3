#include "library_page.h"

#include <QGridLayout>
#include <QSize>
#include <QVideoWidget>

#include "libraryPage/videolibrary.h"
#include "player.h"

LibraryPage::LibraryPage(std::vector<VideoFile *> &videos, Player *player)
    : QWidget() {
  VideoLibrary *library = new VideoLibrary(videos, player);
  QGridLayout *libraryLayout = new QGridLayout();
  libraryLayout->addWidget(library, 0, 0);
  setLayout(libraryLayout);
}
