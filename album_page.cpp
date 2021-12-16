#include "album_page.h"
#include "favourite_page.h"
#include <QVideoWidget>
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>
#include <QLabel>
#include <albumsPage/albumlibrary.h>

AlbumPage::AlbumPage(std::vector<VideoFile> &videos,Player *videoPlayer) : QWidget(), player(videoPlayer), videos(videos) {
    toggler = new QStackedWidget;
    //Create the layouts
    QGridLayout *albumsLayout = new QGridLayout();
    QGridLayout *currentLibrary = new QGridLayout();
    QVBoxLayout *albumsPageLayout = new QVBoxLayout();


    //Create the current album browser. Which is a VideoLibrary + Back button
    VideoLibrary *currentAlbum = new VideoLibrary(videos, player);

    QToolButton *back = new QToolButton();
    back->setIcon(QIcon("://goback-icon"));
    currentLibrary->addWidget(currentAlbum, 0, 0, 3, 1);
    currentLibrary->addWidget(back, 3, 0, 1, 1);

    //Create the album library, for selecting an album
    AlbumLibrary* albumLibrary = new AlbumLibrary(videos, currentAlbum, toggler);
    toggler->addWidget(albumLibrary);
    albumLibrary->setLayout(albumsPageLayout);
    QWidget* libraryWidget = new QWidget();
    libraryWidget->setLayout(currentLibrary);
    toggler->addWidget(libraryWidget);

    //Connect button and add to page
    connect(back, &QToolButton::clicked, albumLibrary, &AlbumLibrary::switchBack);
    albumsLayout->addWidget(toggler, 0, 0);
    setLayout(albumsLayout);
    show();
}


void AlbumPage::showAlbums(){

}
