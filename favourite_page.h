#ifndef THE_FAVOURITE_PAGE_H
#define THE_FAVOURITE_PAGE_H

#include <QWidget>
#include "video_file.h"
#include "player.h"
#include "libraryPage/videolibrary.h"

class FavouritePage : public QWidget {
    Q_OBJECT

public:
    FavouritePage(std::vector<VideoFile> &videos,Player* player);
    void filterForFavourites();

    VideoLibrary *library;

private:
    std::vector<VideoFile> &videos;
};

#endif // THE_FAVOURITE_PAGE_H
