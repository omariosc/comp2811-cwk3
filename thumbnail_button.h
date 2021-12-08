//
// Created by twak on 11/11/2019.
//

#ifndef THE_THUMBNAIL_BUTTON_H
#define THE_THUMBNAIL_BUTTON_H

#include <QPushButton>
#include <QUrl>
#include "video_file.h"

class ThumbnailButton : public QPushButton {
    Q_OBJECT

public:
    VideoFile* info;
    ThumbnailButton(QWidget *parent, VideoFile* i);
    void setFile(VideoFile* i);

private slots:
    void clicked();

signals:
    void jumpTo(VideoFile*);

};

#endif // THE_THUMBNAIL_BUTTON_H

