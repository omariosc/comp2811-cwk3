//
// Created by twak on 11/11/2019.
//

#ifndef ThumbnailButton_H
#define ThumbnailButton_H
#include <QPushButton>
#include <QUrl>
#include "videoFile.h"

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

#endif //CW2_THE_BUTTON_H

