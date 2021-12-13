#ifndef THE_ALBUM_PAGE_H
#define THE_ALBUM_PAGE_H

#include <QWidget>
#include "video_file.h"

class AlbumPage : public QWidget {
    Q_OBJECT

public:
    AlbumPage(std::vector<VideoFile> &videos) : QWidget() {}

};

#endif // THE_ALBUM_PAGE_H
