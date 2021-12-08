//
// Created by twak on 11/11/2019.
//

#include "thumbnail_button.h"

void ThumbnailButton::init(VideoFile* i) {
    setIcon( *(i->icon) );
    info =  i;
}


void ThumbnailButton::clicked() {
    emit jumpTo(info);
}
