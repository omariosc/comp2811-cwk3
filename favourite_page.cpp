#include "favourite_page.h"
#include <QVideoWidget>
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>

FavouritePage::FavouritePage(std::vector<VideoFile> &videos,Player *player) : QWidget(),videos(videos) {
    library = new VideoLibrary(videos,player);
    qDebug() << "We got here";
    //connect(player->returnBack(),&QToolButton::clicked,library,&VideoLibrary::filterForFavourites);
    QGridLayout *libraryLayout = new QGridLayout();
    libraryLayout->addWidget(library, 0, 0);
    setLayout(libraryLayout);
    filterForFavourites();
}


void FavouritePage::filterForFavourites(){
    std::vector<VideoFile> currentVideos;
    for (VideoFile video : videos) {
        if (video.favorite) {
            currentVideos.push_back(video);
        }
    }
    library->changeVideos(currentVideos);
}
