#include "results.h"

Results::Results() {
    QScrollArea();

    setWidget(resultWidget(""));
}

void Results::getCountry(QString country) {
    setWidget(resultWidget(country));
}

QWidget* Results::resultWidget(QString country) {
    if (!country.isEmpty()) {
        QWidget *w = new QWidget();
        QVBoxLayout *container = new QVBoxLayout();
        QGridLayout *resultsLayout = new QGridLayout();

        QWidget *results = new QWidget();
        QLabel *header = new QLabel("Results from " + country + ":");
        header->setStyleSheet("color: #FFFFFF; font: 20px;");

        // Add actual results in when possible
        results->setLayout(resultsLayout);

        container->addWidget(header);
        container->addWidget(results);

        w->setLayout(container);

        return w;
    } else {
        return new QLabel("Select country");
    }
}
