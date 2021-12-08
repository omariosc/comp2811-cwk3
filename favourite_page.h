#ifndef THE_FAVOURITE_PAGE_H
#define THE_FAVOURITE_PAGE_H

#include <QWidget>
#include "video_file.h"

class FavouritePage : public QWidget {
    Q_OBJECT

public:
    FavouritePage(std::vector<VideoFile> &videos) : QWidget() {}

};

#endif // THE_FAVOURITE_PAGE_H
