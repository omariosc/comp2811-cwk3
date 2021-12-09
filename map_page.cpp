#include "map_page.h"

MapPage::MapPage() {
    i = new Image();
    r = new Results();

    QObject::connect(i, &Image::sendCountry, r, &Results::getCountry);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(i);
    l->addWidget(r);

    l->setAlignment(i, Qt::AlignHCenter);
    l->setStretch(1, 0);

    setLayout(l);
}

void MapPage::resizeEvent(QResizeEvent *e) {
    int height = e->size().height();

    i->setFixedHeight(height*0.5);
    r->setFixedHeight(height*0.5);
}
