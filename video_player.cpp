//
// Created by twak on 11/11/2019.
//

#include "video_player.h"
#include "QUrl"

VideoPlayer:: VideoPlayer() : QMediaPlayer(NULL) {
    setVolume(50); // be slightly less annoying
    //connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
//    setMedia(*target.url);
//    play();
}

// change Media being played
void VideoPlayer::setContent(VideoFile* i) {
    if(i != NULL) setMedia(*i->url);
    else{
        printf("We got here");
        setMedia(QUrl::fromLocalFile("P:/Coursework/videos/200IQ.mp4"));
    }
    play();
}
