#include "map_page.h"

MapPage::MapPage(const std::vector<VideoFile> &videos, Player* player) {
    i = new Image();
    r = new Results(videos, player);

    QObject::connect(i, &Image::sendCountry, r, &Results::getCountry);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(i, 50);
    l->addWidget(r, 50);

    l->setAlignment(i, Qt::AlignHCenter);
    //l->setStretch(1, 0);

    setLayout(l);
}

void MapPage::resizeEvent(QResizeEvent *e) {
    int height = e->size().height();

    i->setFixedHeight(height*0.5);
    r->setFixedHeight(height*0.5);
}
