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

class Player : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<VideoFile>* infos;
    std::vector<ThumbnailButton*>* buttons;

public:
    Player() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<ThumbnailButton*>* b, std::vector<VideoFile>* i);

private slots:

    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (VideoFile* button);
};

#endif //THE_PLAYER_H
