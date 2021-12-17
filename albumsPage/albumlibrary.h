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
  void switchToAlbum(); //Display VideoLibrary containing the album's videos
  void switchBack(); //Display the AlbumLibrary again

  void filterForAlbum(int album); //Filter for videos in an album, then display it in VideoLibrary

 private:
  std::vector<AlbumButton*> buttons; //holds the buttons triggering Album Selection
  std::vector<VideoFile*>& videos;
  VideoLibrary* library; //pointer to the VideoLibrary displaying the album videos
  QStackedWidget* toggler; //Pointer to the stacked widget holding this object and the library above
  QWidget* buttonScrollArea;
};

#endif  // ALBUMLIBRARY_H
