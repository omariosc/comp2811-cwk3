#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include <QScrollArea>
#include "video_file.h"
#include "thumbnail_button.h"
#include "player.h"

class VideoLibrary : public QScrollArea {
    Q_OBJECT

public:
    VideoLibrary(std::vector<VideoFile> &vids, Player &player);
    std::vector<ThumbnailButton*>* getButtons();

private:
    std::vector<ThumbnailButton*> buttons;
    std::vector<VideoFile> videos;
};

#endif // VIDEOLIBRARY_H
