#include "map_page.h"

MapPage::MapPage(const std::vector<VideoFile*> &videos, Player* player) {
    i = new Image();
    r = new Results(videos, player);

    QObject::connect(i, &Image::sendCountry, r, &Results::getCountry);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(i);
    l->addWidget(r);

    l->setAlignment(i, Qt::AlignTop);
    l->setAlignment(i, Qt::AlignHCenter);
    l->setMargin(0);

    setLayout(l);
}

void MapPage::resizeEvent(QResizeEvent *e) {
    int height = e->size().height();
    int width = e->size().width();

    i->setFixedSize(width, height*0.5);
}
