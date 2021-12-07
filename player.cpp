//
// Created by twak on 11/11/2019.
//

#include "player.h"

// all buttons have been setup, store pointers here
void Player::setContent(std::vector<ThumbnailButton*>* b, std::vector<VideoFile>* i) {
    buttons = b;
    infos = i;
    jumpTo(buttons -> at(0) -> info);
}

// change the image and video for one button every one second
void Player::shuffle() {
    VideoFile* i = & infos -> at (rand() % infos->size() );
//        setMedia(*i->url);
    buttons -> at( updateCount++ % buttons->size() ) -> setFile( i );
}

void Player::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
            break;
    default:
        break;
    }
}

void Player::jumpTo (VideoFile* button) {
    setMedia( * button -> url);
    play();
}
