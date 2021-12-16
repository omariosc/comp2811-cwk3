#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include <QScrollArea>
#include "video_file.h"
#include "thumbnail_button.h"
#include "player.h"

class VideoLibrary : public QScrollArea {
    Q_OBJECT

public:
    VideoLibrary(std::vector<VideoFile> &vids, Player* player);
    void setVideos(std::vector<VideoFile> &vids);
    std::vector<ThumbnailButton*>* getButtons();

public slots:
    void changeVideos(std::vector<VideoFile> &vids);
    void filterForFavourites();
    void filterForAlbum(int album);

private:
    std::vector<ThumbnailButton*> buttons;
    std::vector<VideoFile> videos;
    std::vector<VideoFile> allVideos;
    QWidget *buttonScrollArea;
    Player* mediaPlayer;
};

#endif // VIDEOLIBRARY_H
