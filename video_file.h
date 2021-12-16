#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QIcon>
#include <QUrl>

class VideoFile {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    QIcon* original; //original icon
    int album;

    VideoFile ( QUrl* url, QIcon* icon, bool favorite = false);
    void setIcon(QIcon* icon);
    void setFavourite(bool flag);
    bool getFavourite();
private:
    bool favorite;
};


#endif // THE_VIDEO_FILE_H
