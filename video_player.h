//
// Created by twak on 11/11/2019.
//

#ifndef THE_PLAYER_H
#define THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "thumbnail_button.h"
#include <vector>
#include <QTimer>

class VideoPlayer : public QMediaPlayer {

Q_OBJECT

public:
    VideoPlayer();
    // all buttons have been setup, store pointers here
    void setContent(VideoFile* i);

public slots:
    // start playing this ButtonInfo

private slots:
    // change the image and video for one button every one second

private:
    VideoFile* video;
};

#endif //THE_PLAYER_H
