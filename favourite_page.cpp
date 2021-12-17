#include "favourite_page.h"

#include <QGridLayout>
#include <QSize>
#include <QVideoWidget>

#include "libraryPage/videolibrary.h"
#include "main_window.h"

FavouritePage::FavouritePage(std::vector<VideoFile *> &videos, Player *player)
    : QWidget(), videos(videos) {
  //Create a video library and display it
  library = new VideoLibrary(videos, player);
  QGridLayout *libraryLayout = new QGridLayout();
  libraryLayout->addWidget(library, 0, 0);
  setLayout(libraryLayout);
  //display only favourited videos
  filterForFavourites();
  //Whenever the video player quits,
  //refresh to account for added/removed favourite videos
  connect(player, &Player::playerQuit, this,
          &FavouritePage::filterForFavourites);
}


//Filter for favourited videos in the videos list, then prompt the VideoLibrary to display them.
void FavouritePage::filterForFavourites() {
  std::vector<VideoFile *> currentVideos;
  for (VideoFile *video : videos) {
    if (video->getFavourite()) {
      currentVideos.push_back(video);
    }
  }
  library->changeVideos(currentVideos);
}

//Refresh the VideoLibrary.
void FavouritePage::refresh() { library->refresh(); }
