//
// Created by twak on 11/11/2019.
//

#include "thumbnail_button.h"

ThumbnailButton::ThumbnailButton(QWidget *parent, VideoFile* i) :  QPushButton(parent) {
    setFile(i);
    setIconSize(QSize(200,110));
    connect(this, SIGNAL(released()), this, SLOT (clicked() ));
}

void ThumbnailButton::setFile(VideoFile* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void ThumbnailButton::clicked() {
    emit jumpTo(info);
}
