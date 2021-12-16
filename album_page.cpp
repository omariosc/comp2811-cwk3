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
    //Create the layouts
    QGridLayout *albumsLayout = new QGridLayout();
    QVBoxLayout *currentLibrary = new QVBoxLayout();

    //Create the current album browser. Which is a VideoLibrary + Back button
    VideoLibrary *currentAlbum = new VideoLibrary(videos,player);
    QToolButton *back = new QToolButton();
    back->setIcon(QIcon("://goback-icon"));
    currentLibrary->addWidget(currentAlbum);
    currentLibrary->addWidget(back);

    //Create the album library, for selecting an album
    AlbumLibrary* albumlibrary = new AlbumLibrary(videos,currentAlbum,toggler);
    toggler->addWidget(albumlibrary);
    QWidget* libraryWidget = new QWidget();
    libraryWidget->setLayout(currentLibrary);
    toggler->addWidget(libraryWidget);

    //Connect button and add to page
    connect(back,&QToolButton::clicked,albumlibrary,&AlbumLibrary::switchBack);
    albumsLayout->addWidget(toggler, 0, 0);
    setLayout(albumsLayout);
    show();
}


void AlbumPage::showAlbums(){

}
