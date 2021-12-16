#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QIcon>
#include <QUrl>

class VideoFile {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    bool favorite;
    int album;

    VideoFile ( QUrl* url, QIcon* icon, bool favorite = false) : url (url), icon (icon), favorite(favorite) {}
};


#endif // THE_VIDEO_FILE_H
