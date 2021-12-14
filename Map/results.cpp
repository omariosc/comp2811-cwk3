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

    // Randomize video vector
    std::random_device rd;
    auto rng = std::default_random_engine { rd() };
    std::shuffle(std::begin(v), std::end(v), rng);

    auto randomVideos = std::vector<VideoFile>(v.begin(), v.begin()+4);

    // Remove the results widget, recreate it (with new videos) and re-add it
    this->layout()->removeWidget(results);
    results = new VideoLibrary(randomVideos, p);
    this->layout()->addWidget(results);
}
