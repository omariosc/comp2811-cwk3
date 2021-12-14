#include "results.h"

Results::Results(const std::vector<VideoFile> &videos, Player* player) {
    QScrollArea();

    v = videos;
    p = player;

    header = new QLabel();
    header->setText("Select country");

    header->setStyleSheet("color: #FFFFFF; font: 20px;");

    results = new QWidget();

    QVBoxLayout *l = new QVBoxLayout();

    l->addWidget(header);
    l->addWidget(results);

    setLayout(l);
}

void Results::getCountry(QString country) {
    updateWidget(country);
}

void Results::updateWidget(QString country) {
    if (!country.isEmpty()) {
        header->setText("Results from " + country + ":");
    }

    this->layout()->removeWidget(results);
    results = new VideoLibrary(v, p);
    this->layout()->addWidget(results);
}
