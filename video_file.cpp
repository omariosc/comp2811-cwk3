#include "video_file.h"
#include "QPainter"
#include "qdebug.h"
#include <QDebug>

VideoFile::VideoFile( QUrl* url, QIcon* icon, bool favourite) : url (url), favourite(favourite), originalIcon(icon) {
    updateIcon();
    hasMetaData = false;
}

void VideoFile::setMeta(QString metadata){
    QStringList splitData(metadata.split(","));
    creationDate = QDate::fromString(splitData[0], "dd/MM/yyyy");
    videoLength = splitData[1].toInt();
    city = splitData[2];
    countryCode = splitData[3];
    hasMetaData = true;
}

void VideoFile::updateIcon(QIcon* newIcon){
    if (newIcon) {
        originalIcon = newIcon;
    }
    newIcon = originalIcon;
    if (favourite) {
        QPixmap base, overlay;
        base = newIcon->pixmap(128,128);
        overlay = QPixmap(":/favouritesOverlay");
        QPixmap result(base.width(), base.height());
        result.fill(Qt::transparent);
        QPainter painter(&result);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(0, 0, overlay);
        icon = QIcon(result);
    }
    else {
        icon = *newIcon;
    }
}

void VideoFile::setFavourite(bool flag){
    favourite = flag;
    updateIcon();
}

void VideoFile::toggleFavourite(){
    favourite = !favourite;
    updateIcon();
}

bool VideoFile::getFavourite(){
    return favourite;
}

bool VideoFile::hasMeta() {
    return hasMetaData;
}


QDate VideoFile::getDate(){
    return creationDate;
}

int VideoFile::getLen(){
    return videoLength;
}

QString VideoFile::getLocation(){
    return city + ", " + countryCode;
}
