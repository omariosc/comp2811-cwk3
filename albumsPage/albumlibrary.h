#ifndef ALBUMLIBRARY_H
#define ALBUMLIBRARY_H

#include <albumsPage/albumbutton.h>
#include <libraryPage/videolibrary.h>

#include <QScrollArea>
#include <QWidget>

#include "player.h"

class AlbumLibrary : public QScrollArea {
  Q_OBJECT
 public:
  AlbumLibrary(std::vector<VideoFile*>& vids, VideoLibrary* library,
               QStackedWidget* toggler);
  void setAlbums();

 public slots:
  void switchToAlbum();
  void switchBack();

  void filterForAlbum(int album);

 private:
  std::vector<AlbumButton*> buttons;
  std::vector<VideoFile*>& videos;
  VideoLibrary* library;
  QStackedWidget* toggler;
  QWidget* buttonScrollArea;
};

#endif  // ALBUMLIBRARY_H
