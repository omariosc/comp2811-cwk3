//
// Created by twak on 11/11/2019.
//

#include "thumbnail_button.h"

#include <QIcon>
#include <QSizePolicy>

ThumbnailButton::ThumbnailButton(QWidget* parent) : QToolButton(parent) {
  QSizePolicy buttonSizePolicy;
  buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  buttonSizePolicy.setWidthForHeight(1);
  setSizePolicy(buttonSizePolicy);

  setMinimumHeight(45);

  connect(this, &ThumbnailButton::released, this, &ThumbnailButton::clicked);
}

void ThumbnailButton::init(VideoFile* i) {
  setIcon(i->icon);
  setIconSize(QSize(96, 80));

  info = i;
}

void ThumbnailButton::clicked() { emit jumpTo(info); }
