#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QIcon>
#include <QUrl>

class VideoFile {

public:
    QUrl* url; // video file to play
    QIcon icon; // icon to display
    int album;

    VideoFile ( QUrl* url, QIcon* icon, bool favorite = false);
    void updateIcon(QIcon* icon=NULL);
    void setFavourite(bool flag);
    void toggleFavourite();
    bool getFavourite();
    QUrl getUrl() {return *url;}

private:
    bool favorite;
    QIcon* originalIcon;
};


#endif // THE_VIDEO_FILE_H
