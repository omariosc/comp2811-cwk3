#ifndef THE_VIDEO_FILE_H
#define THE_VIDEO_FILE_H

#include <QIcon>
#include <QUrl>

class VideoFile {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display

    VideoFile ( QUrl* url, QIcon* icon) : url (url), icon (icon) {}
};


#endif // THE_VIDEO_FILE_H
