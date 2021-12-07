#include "map.h"

Map::Map() {
    setMinimumSize(1280, 720);
    setMaximumSize(1920, 1080);

    QVBoxLayout *l = new QVBoxLayout();
    l->addWidget(new Image());
    l->addWidget(new Results());

    setLayout(l);
}
