//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "thumbnailButton.h"
#include <vector>
#include <QTimer>

class Player : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<VideoFile>* infos;
    std::vector<ThumbnailButton*>* buttons;
    QTimer* mTimer;
    long updateCount = 0;

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

private slots:

    // change the image and video for one button every one second
    void shuffle();

    void playStateChanged (QMediaPlayer::State ms);

public slots:

    // start playing this ButtonInfo
    void jumpTo (VideoFile* button);
};

#endif //CW2_THE_PLAYER_H
