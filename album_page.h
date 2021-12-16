#ifndef THE_ALBUM_PAGE_H
#define THE_ALBUM_PAGE_H

#include <QWidget>
#include "video_file.h"
#include "player.h"
#include "libraryPage/videolibrary.h"

class AlbumPage : public QWidget {
    Q_OBJECT

public:
    AlbumPage(std::vector<VideoFile*> &videos,Player* player);

public slots:
    void refreshCurrent();

private:
    void showAlbums();
    VideoLibrary * currentAlbum;
    QStackedWidget* toggler;
    Player* player;
    std::vector<VideoFile*> videos;
};

#endif // THE_ALBUM_PAGE_H
