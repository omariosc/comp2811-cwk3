#include "albumlibrary.h"

#include <QPushButton>
#include <string>

static unsigned int hardAlbumsNr = 3;

AlbumLibrary::AlbumLibrary(std::vector<VideoFile*>& vids, VideoLibrary* library,
                           QStackedWidget* toggler)
    : videos(vids), library(library), toggler(toggler) {
  setWidgetResizable(1);
  buttonScrollArea = new QScrollArea();
  setAlbums();
}

void AlbumLibrary::setAlbums() {
   //clear existing layouts and widgets
  delete buttonScrollArea;
  buttons.clear();

  //create new scrollableArea
  buttonScrollArea = new QWidget();
  buttonScrollArea->setProperty("type", "content");

  //Create a grid layout for the album buttons to be displayed in
  QGridLayout* layout = new QGridLayout();
  //Ensure we always have 2 columns, even with only 1 album.
  layout->setColumnStretch(0, 1);
  layout->setColumnStretch(1, 1);

  QSizePolicy buttonScrollAreaSizePolicy = QSizePolicy();
  buttonScrollAreaSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  layout->setMargin(0);
  layout->setSpacing(0);
  buttonScrollArea->setLayout(layout);

  unsigned int i = 0;
  //Add all the albums to the layout
  for (i = 0; i < hardAlbumsNr; i++) {
    AlbumButton* button = new AlbumButton(buttonScrollArea);
    button->setAlbum(i + 1); //Set the album's ID
    QString name = "ALBUM " + QString::number(i + 1); //Name the albums based on their index and album ID
    button->setText(name);
    button->connect(button, SIGNAL(changeAlbum(int)), this,
                    SLOT(filterForAlbum(int)));
    buttons.push_back(button);
    layout->addWidget(button, i / 2, i % 2);
  }

  //Add the "Add Album" button
  QToolButton* add = new QToolButton();
  add->setProperty("type", "albumButton");
  add->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  add->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
  add->setMinimumHeight(45);
  add->setText("New Album");
  add->setIcon(QIcon(":/addLibraryIcon"));
  add->setIconSize(QSize(50, 60));
  layout->addWidget(add, i / 2, i % 2);

  setWidget(buttonScrollArea);
  buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);
}

void AlbumLibrary::switchToAlbum() { toggler->setCurrentIndex(1); }

void AlbumLibrary::switchBack() { toggler->setCurrentIndex(0); }

//Go through the videos, filter for videos with the provided album ID
//Then pass the filtered videos to the video player
void AlbumLibrary::filterForAlbum(int album) {
  std::vector<VideoFile*> currentVideos;
  for (VideoFile* video : videos) {
    if (video->album == album) {
      currentVideos.push_back(video);
    }
  }
  switchToAlbum();
  library->changeVideos(currentVideos);
}
