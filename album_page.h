#ifndef THE_ALBUM_PAGE_H
#define THE_ALBUM_PAGE_H

#include <QWidget>

#include "libraryPage/videolibrary.h"
#include "player.h"
#include "video_file.h"

class AlbumPage : public QWidget {
  Q_OBJECT

 public:
  AlbumPage(std::vector<VideoFile*>& videos, Player* player);

 public slots:
  void refreshCurrent(); // Refresh library

 private:
  void showAlbums();
  VideoLibrary* currentAlbum;
  QStackedWidget* stackedParent;  // switches between albums and videolibrary
  Player* player;
  std::vector<VideoFile*> videos;
};

#endif  // THE_ALBUM_PAGE_H
