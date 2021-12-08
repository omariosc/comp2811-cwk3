#include "results.h"

Results::Results() {
    QScrollArea();

    setWidget(new QLabel("Hello"));
}

void Results::getCountry(QString country) {
    qDebug() << country;
}
