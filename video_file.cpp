#include "video_file.h"

#include <QDebug>

#include "QPainter"
#include "qdebug.h"

VideoFile::VideoFile(QUrl* url, QIcon* icon, bool favourite)
    : url(url), favourite(favourite), originalIcon(icon) {
  // call update icon as icon may have to be set to version with favourites star
  updateIcon();
  hasMetaData = false;
}

void VideoFile::setMeta(QString metadata) {
  // string parsing of metadata file input to relevant fields
  QStringList splitData(metadata.split(","));
  creationDate = QDate::fromString(splitData[0], "dd/MM/yyyy");
  videoLength = splitData[1].toInt();
  city = splitData[2];
  countryCode = splitData[3];
  hasMetaData = true;
}

void VideoFile::updateIcon(QIcon* newIcon) {
  if (newIcon) {
    originalIcon = newIcon;
  }
  newIcon = originalIcon;
  if (favourite) {
    // Overlay favourites star on icon and save it as new icon if video is favourited
    QPixmap base, overlay;
    base = newIcon->pixmap(128, 128);
    overlay = QPixmap(":/favouritesOverlay");
    QPixmap result(base.width(), base.height());
    result.fill(Qt::transparent);
    QPainter painter(&result);
    painter.drawPixmap(0, 0, base);
    painter.drawPixmap(0, 0, overlay);
    icon = QIcon(result);
  } else {
    //otherwise, display the icon as is
    icon = *newIcon;
  }
}

void VideoFile::setFavourite(bool flag) {
  favourite = flag;
  updateIcon(); //ensure the icon reflects the change in favourite status
}

void VideoFile::toggleFavourite() {
  favourite = !favourite;
  updateIcon(); //ensure the icon reflects the change in favourite status
}

bool VideoFile::getFavourite() { return favourite; }

bool VideoFile::hasMeta() { return hasMetaData; }

QDate VideoFile::getDate() { return creationDate; }

int VideoFile::getLen() { return videoLength; }

QString VideoFile::getLocation() { return city + ", " + countryCode; }
