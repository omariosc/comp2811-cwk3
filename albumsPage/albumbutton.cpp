#include "albumbutton.h"
#include <QDebug>
#include <QIcon>
#include <QSizePolicy>

AlbumButton::AlbumButton(QWidget *parent) : QToolButton(parent) {
  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  QSizePolicy buttonSizePolicy;
  buttonSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
  buttonSizePolicy.setWidthForHeight(1);
  setSizePolicy(buttonSizePolicy);
  setMinimumHeight(45);
  connect(this, SIGNAL(released()), this, SLOT(clicked()));
  init(1);
}

void AlbumButton::init(int album) {
  setIcon(QIcon(":/albumsIcon"));
  setIconSize(QSize(50, 60));
  albumNr = album;
}

void AlbumButton::clicked() { emit changeAlbum(albumNr); }

void AlbumButton::setAlbum(int album) { albumNr = album; }
