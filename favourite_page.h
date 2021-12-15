#ifndef THE_FAVOURITE_PAGE_H
#define THE_FAVOURITE_PAGE_H

#include <QWidget>
#include "video_file.h"
#include "player.h"

class FavouritePage : public QWidget {
    Q_OBJECT

public:
    FavouritePage(std::vector<VideoFile> &videos,Player* player);
};

#endif // THE_FAVOURITE_PAGE_H
