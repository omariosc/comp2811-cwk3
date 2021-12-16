#ifndef ALBUMLIBRARY_H
#define ALBUMLIBRARY_H

#include <QWidget>
#include "player.h"
#include <QScrollArea>
#include <albumsPage/albumbutton.h>

class AlbumLibrary: public QScrollArea
{
public:
    AlbumLibrary(std::vector<VideoFile> &vids, Player* player);
    void setAlbums();

private:
    std::vector<AlbumButton*> buttons;
    std::vector<VideoFile> videos;
    Player* player;
    QWidget *buttonScrollArea;
};

#endif // ALBUMLIBRARY_H
