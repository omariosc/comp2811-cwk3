#ifndef THE_ALBUM_PAGE_H
#define THE_ALBUM_PAGE_H

#include <QWidget>
#include "video_file.h"
#include "player.h"

class AlbumPage : public QWidget {
    Q_OBJECT

public:
    AlbumPage(std::vector<VideoFile> &videos,Player* player);

private:
    void showAlbums();

    QStackedWidget* toggler;
    Player* player;
    std::vector<VideoFile> videos;
};

#endif // THE_ALBUM_PAGE_H
