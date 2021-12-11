//
// Created by twak on 11/11/2019.
//

#include "thumbnail_button.h"
#include <QIcon>
#include <QSizePolicy>

ThumbnailButton::ThumbnailButton(QWidget *parent) :  QToolButton(parent) {
    QSizePolicy buttonSizePolicy;
    buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
    buttonSizePolicy.setWidthForHeight(1);
    setSizePolicy(buttonSizePolicy);
    iconWidth = parent->width()-10;
    setMinimumHeight(400);
    connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
}

void ThumbnailButton::init(VideoFile* i) {
    setIcon( *i->icon );
    setIconSize(QSize(width(),height()));
    info =  i;
}


void ThumbnailButton::clicked() {
    emit jumpTo(info);
}
