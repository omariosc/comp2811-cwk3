#include "results.h"

Results::Results() {
    QScrollArea();

    header = new QLabel();
    header->setText("Select country");

    header->setStyleSheet("color: #FFFFFF; font: 20px;");

    // Add results later
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

    // Update results here
}
