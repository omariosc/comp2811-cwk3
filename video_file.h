#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QDate>
#include <QIcon>
#include <QUrl>

class VideoFile {
 public:
  QUrl* url;   // video file to play
  QIcon icon;  // icon to display
  int album;

  VideoFile(QUrl* url, QIcon* icon, bool favourite = false);
  void updateIcon(QIcon* icon = NULL);
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
  QDate creationDate;
  int videoLength;
  QString city;
  QString countryCode;

  bool favourite;
  QIcon* originalIcon;
};

#endif  // THE_VIDEO_FILE_H
