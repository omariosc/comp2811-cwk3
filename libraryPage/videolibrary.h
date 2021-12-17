#ifndef VIDEOLIBRARY_H
#define VIDEOLIBRARY_H

#include <QScrollArea>

#include "player.h"
#include "thumbnail_button.h"
#include "video_file.h"

class VideoLibrary : public QScrollArea {
  Q_OBJECT

 public:
  VideoLibrary(std::vector<VideoFile *> &vids, Player *player);
  void setVideos(std::vector<VideoFile *> &vids); // Set the videos that are currently displayed
  std::vector<ThumbnailButton *> *getButtons(); // Return buttons

 public slots:
  void changeVideos(std::vector<VideoFile *> &vids);
  void refresh(); // Refresh for layout

 private:
  std::vector<ThumbnailButton *> buttons;
  std::vector<VideoFile *> videos;
  QWidget *buttonScrollArea;
  Player *mediaPlayer;
};

#endif  // VIDEOLIBRARY_H
