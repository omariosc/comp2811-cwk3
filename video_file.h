#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QIcon>
#include <QUrl>
#include <QDate>

class VideoFile {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    bool favorite;

    VideoFile (QUrl* url, QIcon* icon, bool favorite = false);
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
};


#endif // THE_VIDEO_FILE_H
