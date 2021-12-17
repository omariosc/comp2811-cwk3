#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QDate>
#include <QIcon>
#include <QUrl>

class VideoFile {
 public:
  QUrl* url;   // video file to play
  QIcon icon;  // icon to display
  int album;   // used to place video in albums

  VideoFile(QUrl* url, QIcon* icon, bool favourite = false); // Assume isn't favourite
  void updateIcon(QIcon* icon = NULL); // Updates the icon to either be a new iamge or to add favourite overlay
  void setFavourite(bool flag);
  void toggleFavourite();
  bool getFavourite();
  QUrl getUrl() { return *url; }

  void setMeta(QString metadata);
  bool hasMeta();
  QDate getDate();
  int getLen();
  QString getLocation();

 private:
  bool hasMetaData;
  QDate creationDate; // Creation of date of video
  int videoLength; // Length of video in seconds
  QString city; // City of location
  QString countryCode; // 2 digit code of country location
  bool favourite; // If video is favourited
  QIcon* originalIcon; // Pointer to non overlayed icon image
};

#endif  // THE_VIDEO_FILE_H
