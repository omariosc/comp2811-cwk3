//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//  2811 cw3 : twak 11/11/2021
//

#include <QApplication>
#include <QDesktopServices>
#include <QImageReader>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtCore/QFileInfo>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QtWidgets/QFileIconProvider>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <iostream>
#include <string>
#include <vector>

#include "album_page.h"
#include "favourite_page.h"
#include "filter_page.h"
#include "library_page.h"
#include "mainPage/navigation_button.h"
#include "mainPage/title_label.h"
#include "main_window.h"
#include "map_page.h"
#include "player.h"
#include "settingspage.h"
#include "thumbnail_button.h"
#include "video_player.h"

// read in videos and thumbnails to this directory
std::vector<VideoFile> getInfoIn(std::string loc) {
  std::vector<VideoFile> out = std::vector<VideoFile>();
  QDir dir(QString::fromStdString(loc));
  QDirIterator it(dir);

  while (it.hasNext()) {  // for all files

    QString f = it.next();

    if (f.contains("."))

#if defined(_WIN32)
      if (f.contains(".wmv")) {  // windows
#else
      if (f.contains(".mp4") || f.contains("MOV")) {  // mac/linux
#endif

        QString thumb = f.left(f.length() - 4) + ".png";
        if (QFile(thumb).exists()) {  // if a png thumbnail exists
          QImageReader* imageReader = new QImageReader(thumb);
          QImage sprite = imageReader->read();  // read the thumbnail
          if (!sprite.isNull()) {
            QIcon* icon = new QIcon(QPixmap::fromImage(
                sprite));  // voodoo to create an icon for the button
            QUrl* url = new QUrl(QUrl::fromLocalFile(
                f));  // convert the file location to a generic url

            out.push_back(VideoFile(url, icon));  // add to the output list
            // Checks if file for meta data  exists and if so reads it and sets to file.
            QString meta = f.left(f.length() - 4) + ".metadata";
            QFile metaFile(meta);
            if (metaFile.exists()) {
              if (metaFile.open(QFile::ReadOnly)) {
                QTextStream in(&metaFile);
                QString metaData = in.readAll();
                metaFile.close();
                out.back().setMeta(metaData);
              }
            }
          } else
            qDebug() << "warning: skipping video because I couldn't process "
                        "thumbnail "
                     << thumb;
        } else
          qDebug()
              << "warning: skipping video because I couldn't find thumbnail "
              << thumb;
      }
  }

  return out;
}

int main(int argc, char* argv[]) {
  // Let's just check that Qt is operational first
  qDebug() << "Qt version: " << QT_VERSION_STR;

  // Create the Qt Application
  QApplication app(argc, argv);

  // Collect all the videos in the folder
  // "videos" is a vector of pointers to VideoFiles so that when a videofile is edited it will work globally
  // "actualVideos" is a vecotr of VideoFiles so that the pointers do not fall out of scope
  // If new VideoFiles would need to be added to/removed from actualVideos then the pointers in videos should be recalculated
  std::vector<VideoFile*> videos;
  std::vector<VideoFile> actualVideos;

  if (argc == 2) {
    actualVideos = getInfoIn(std::string(argv[1]));
    for (unsigned int i = 0; i < actualVideos.size(); i++) {
      videos.push_back(&actualVideos[i]);
    }
  }

  if (videos.size() == 0) {
    const int result = QMessageBox::question(
        NULL, QString("Tomeo"),
        QString("no videos found! download, unzip, and add command line "
                "argument to \"quoted\" file location. Download videos from "
                "Tom's OneDrive?"),
        QMessageBox::Yes | QMessageBox::No);

    switch (result) {
      case QMessageBox::Yes:
        QDesktopServices::openUrl(
            QUrl("https://leeds365-my.sharepoint.com/:u:/g/personal/"
                 "scstke_leeds_ac_uk/"
                 "EcGntcL-K3JOiaZF4T_uaA4BHn6USbq2E55kF_BTfdpPag?e=n1qfuN"));
        break;
      default:
        break;
    }
    exit(-1);
  }

  // Add random album numbers to each video
  for (unsigned int x = 0; x < videos.size(); x++) {
    videos.at(x)->album = rand() % 3 + 1;
  }
  // Override some for testing
  videos.at(0)->album = 1;
  videos.at(1)->album = 2;
  videos.at(2)->album = 3;

  // Retrieving stylesheet
  QFile File(":/tomeoStyleSheet");
  File.open(QFile::ReadOnly);
  QString StyleSheet = QLatin1String(File.readAll());

  // Add video "metadata"
  videos[0]->setFavourite(true);
  videos[2]->setFavourite(true);
  videos[3]->setFavourite(true);
  // Create the main window and layout
  QStackedWidget* menu = new QStackedWidget;
  Player* player = new Player(videos[0], menu);
  menu->addWidget(new MainWindow(videos, menu, player));
  menu->addWidget(player);
  menu->addWidget(new SettingsPage(menu));
  menu->setCurrentIndex(0);
  menu->setStyleSheet(StyleSheet);

  // Changing window information
  menu->setWindowTitle("tomeo");
  menu->resize(320, 568);
  menu->setMinimumSize(320, 320);
  menu->show();

  return app.exec();
}
