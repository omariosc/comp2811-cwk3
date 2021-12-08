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

public:
    Player() : QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );

        mTimer = new QTimer(NULL);
        mTimer->setInterval(1000); // 1000ms is one second between ...
        mTimer->start();
        connect( mTimer, SIGNAL (timeout()), SLOT ( shuffle() ) ); // ...running shuffle method
    }

    // all buttons have been setup, store pointers here
    void setContent(std::vector<ThumbnailButton*>* b, std::vector<VideoFile>* i);

public slots:
    // start playing this ButtonInfo
    void jumpTo (VideoFile* button);

private slots:
    // change the image and video for one button every one second
    void shuffle();
    void playStateChanged(QMediaPlayer::State ms);

private:
    std::vector<VideoFile>* infos;
    std::vector<ThumbnailButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;
};

#endif //THE_PLAYER_H
