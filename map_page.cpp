#include "map_page.h"

MapPage::MapPage(const std::vector<VideoFile *> &videos, Player *player) {
  i = new Image();
  r = new Results(videos, player);

  QObject::connect(i, &Image::sendCountry, r, &Results::getCountry);

  QVBoxLayout *l = new QVBoxLayout();
  l->addWidget(i);
  l->addWidget(r);

  // Set alignment of image
  l->setAlignment(i, Qt::AlignTop);
  l->setAlignment(i, Qt::AlignHCenter);

  setLayout(l);
}

void MapPage::resizeEvent(QResizeEvent *e) {
  int height = e->size().height();
  int width = e->size().width();

  // Maximum height image can take up half its the widget
  i->setFixedSize(width - 20, height * 0.5);
}

void MapPage::refresh() { r->refresh(); }
