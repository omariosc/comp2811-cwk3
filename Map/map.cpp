#include "map.h"

Map::Map() {
    setMinimumSize(1280, 720);
    setMaximumSize(1920, 1080);

    auto i = new Image();
    auto r = new Results();

    QObject::connect(i, &Image::sendCountry, r, &Results::getCountry);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(i);
    l->addWidget(r);

    l->setAlignment(i, Qt::AlignHCenter);
    l->setStretch(1, 0);

    setLayout(l);
}
