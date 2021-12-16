#include "album_page.h"
#include "favourite_page.h"
#include <QVideoWidget>
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>
#include <QLabel>
#include <albumsPage/albumlibrary.h>

AlbumPage::AlbumPage(std::vector<VideoFile> &videos,Player *videoPlayer) : QWidget(),player(videoPlayer),videos(videos) {
    toggler = new QStackedWidget;
    QGridLayout *albumsLayout = new QGridLayout();
    toggler->addWidget(new AlbumLibrary(videos,player));
    albumsLayout->addWidget(toggler, 0, 0);
    setLayout(albumsLayout);
    show();
}


void AlbumPage::showAlbums(){

}
