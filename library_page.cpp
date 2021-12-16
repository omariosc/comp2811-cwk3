#include "library_page.h"
#include <QVideoWidget>
#include "player.h"
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>

LibraryPage::LibraryPage(std::vector<VideoFile*> &videos, Player *player) : QWidget() {
    VideoLibrary *library = new VideoLibrary(videos,player);
    QGridLayout *libraryLayout = new QGridLayout();
    libraryLayout->addWidget(library, 0, 0);
    setLayout(libraryLayout);
}

