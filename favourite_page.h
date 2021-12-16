#ifndef THE_FAVOURITE_PAGE_H
#define THE_FAVOURITE_PAGE_H

#include <QWidget>

#include "libraryPage/videolibrary.h"
#include "player.h"
#include "video_file.h"

class FavouritePage : public QWidget {
  Q_OBJECT

 public:
  FavouritePage(std::vector<VideoFile *> &videos, Player *player);
  void filterForFavourites();

  VideoLibrary *library;

 public slots:
  void refresh();

 private:
  std::vector<VideoFile *> &videos;
};

#endif  // THE_FAVOURITE_PAGE_H
