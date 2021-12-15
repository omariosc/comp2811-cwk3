#include "favourite_page.h"
#include <QVideoWidget>
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>

FavouritePage::FavouritePage(std::vector<VideoFile> &videos,Player *player) : QWidget() {
    VideoLibrary *library = new VideoLibrary(videos,player);
    qDebug() << "We got here";
    library->filterForFavourites();
    connect(player->returnBack(),&QToolButton::clicked,library,&VideoLibrary::filterForFavourites);
    QGridLayout *libraryLayout = new QGridLayout();
    libraryLayout->addWidget(library, 0, 0);
    setLayout(libraryLayout);
}
