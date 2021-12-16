//
// Created by twak on 11/11/2019.
//

#ifndef THE_THUMBNAIL_BUTTON_H
#define THE_THUMBNAIL_BUTTON_H

#include <QToolButton>
#include <QUrl>
#include "video_file.h"

class ThumbnailButton : public QToolButton {
    Q_OBJECT

public:
    VideoFile* info;

    ThumbnailButton(QWidget *parent);

    void init(VideoFile* i);

private slots:
    void clicked();

signals:
    void jumpTo(VideoFile*);
};

#endif //THE_THUMBNAIL_BUTTON_H

