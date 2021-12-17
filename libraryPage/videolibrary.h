#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include "player.h"
#include "thumbnail_button.h"
#include "video_file.h"
#include <QScrollArea>

class VideoLibrary : public QScrollArea {
  Q_OBJECT

public:
  VideoLibrary(std::vector<VideoFile *> &vids, Player *player);
  void setVideos(std::vector<VideoFile *> &vids);
  std::vector<ThumbnailButton *> *getButtons();

public slots:
  void changeVideos(std::vector<VideoFile *> &vids);
  void refresh();

private:
  std::vector<ThumbnailButton *> buttons;
  std::vector<VideoFile *> videos;
  QWidget *buttonScrollArea;
  Player *mediaPlayer;
};

#endif // VIDEOLIBRARY_H
