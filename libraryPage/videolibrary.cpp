#include "libraryPage/videolibrary.h"

#include <QGridLayout>
#include <QPushButton>

#include "player.h"

VideoLibrary::VideoLibrary(std::vector<VideoFile *> &vids, Player *player)
    : QScrollArea(), videos(vids) {
  setWidgetResizable(1);
  mediaPlayer = player;
  setVideos(vids);
  connect(
      player, &Player::playerQuit, this,
      &VideoLibrary::refresh);  // When player quits refresh all videoLibraries
                                // as there might have been changes
}

void VideoLibrary::setVideos(std::vector<VideoFile *> &vids) {
  videos = vids;
  buttonScrollArea = new QWidget();
  buttonScrollArea->setProperty("type", "content");

  QGridLayout *layout = new QGridLayout();
  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 1);
  layout->setColumnStretch(2, 1);
  layout->setColumnStretch(3, 1);
  QSizePolicy buttonScrollAreaSizePolicy = QSizePolicy();
  buttonScrollAreaSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  layout->setMargin(0);
  layout->setSpacing(0);
  buttonScrollArea->setLayout(layout);

  for (unsigned int i = 0; i < videos.size(); i++) {
    ThumbnailButton *button = new ThumbnailButton(buttonScrollArea);
    connect(button, &ThumbnailButton::jumpTo, mediaPlayer, &Player::playVid);
    buttons.push_back(button);
    layout->addWidget(button, i / 4, i % 4);  // Places
    button->init(videos.at(i));
  }

  setWidget(buttonScrollArea);
  buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);
}

std::vector<ThumbnailButton *> *VideoLibrary::getButtons() {
  return &(buttons);
}

void VideoLibrary::changeVideos(std::vector<VideoFile *> &vids) {
  delete buttonScrollArea;  // Delete button scroll area for all new widget with
                            // new layout
  buttons.clear();
  // Otherwise keep the current videos and just update layout
  if (&vids != &videos) {
    videos.clear();
  }
  setVideos(vids);
}

void VideoLibrary::refresh() { changeVideos(videos); }
