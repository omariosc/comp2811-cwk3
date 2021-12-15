#include "video_file.h"
#include <QDebug>

VideoFile::VideoFile( QUrl* url, QIcon* icon, bool favorite) : url (url), icon (icon), favorite(favorite) {
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
