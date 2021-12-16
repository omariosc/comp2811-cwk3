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
    setMinimumHeight(45);
    connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
}

void ThumbnailButton::init(VideoFile* i) {
    setIcon(i->icon);
    setIconSize(QSize(48,40));
    info =  i;
}


void ThumbnailButton::clicked() {
    emit jumpTo(info);
}
