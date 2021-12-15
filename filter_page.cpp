#include "filter_page.h"

#include "libraryPage/videolibrary.h"
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QDateEdit>
#include <QSpinBox>
#include <QPushButton>


FilterPage::FilterPage(std::vector<VideoFile> &videos, Player *player) : QWidget() {

    allVideos = videos;
    mediaPlayer = player;

    QLabel*  afterDateLabel = new QLabel("After date: ");
    afterDateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    afterDateLabel->setProperty("type", "filterLabel");
    afterDate = new QDateEdit();

    QLabel* beforeDateLabel = new QLabel("Before date: ");
    beforeDateLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    beforeDateLabel->setProperty("type", "filterLabel");
    beforeDate = new QDateEdit();

    QStringList units = {"Seconds", "Minutes", "Hours"};

    QLabel* longerThanLabel = new QLabel("Longer than: ");
    longerThanLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    longerThanLabel->setProperty("type", "filterLabel");
    longerThanSB = new QSpinBox();
    longerThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    longerThanCB = new QComboBox();
    longerThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    longerThanCB->addItems(units);

    QLabel* shorterThanLabel = new QLabel("Shorter than: ");
    shorterThanLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    shorterThanLabel->setProperty("type", "filterLabel");
    shorterThanSB = new QSpinBox();
    shorterThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    shorterThanCB = new QComboBox();
    shorterThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    shorterThanCB->addItems(units);

    QStringList locations = {"LEEDS, UK", "SNOWDON, UK", "PYONGYANG, NK"};
    QLabel* locationLabel = new QLabel("Location: ");
    locationLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    locationLabel->setProperty("type", "filterLabel");
    locationLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    locationCB = new QComboBox();
    locationCB->addItems(locations);

    QPushButton* makeChanges = new QPushButton();
    makeChanges->setText("APPLY FILTER");
    makeChanges->setProperty("type", "filter");
    connect(makeChanges, &QPushButton::clicked, this, &FilterPage::applyChanges);

    library = new VideoLibrary(videos, mediaPlayer);

    QGridLayout *filterLayout = new QGridLayout();
    filterLayout->setColumnStretch(0, 1);
    filterLayout->setColumnStretch(1, 1);
    filterLayout->setColumnStretch(2, 1);
    filterLayout->setColumnStretch(3, 1);

    filterLayout->addWidget(afterDateLabel,     0, 0, 1, 2);
    filterLayout->addWidget(afterDate,          0, 2, 1, 2);

    filterLayout->addWidget(beforeDateLabel,    1, 0, 1, 2);
    filterLayout->addWidget(beforeDate,         1, 2, 1, 2);

    filterLayout->addWidget(longerThanLabel,    2, 0, 1, 2);
    filterLayout->addWidget(longerThanSB,       2, 2, 1, 1);
    filterLayout->addWidget(longerThanCB,       2, 3, 1, 1);

    filterLayout->addWidget(shorterThanLabel,   3, 0, 1, 2);
    filterLayout->addWidget(shorterThanSB,      3, 2, 1, 1);
    filterLayout->addWidget(shorterThanCB,      3, 3, 1, 1);

    filterLayout->addWidget(locationLabel,      4, 0, 1, 2);
    filterLayout->addWidget(locationCB,         4, 2, 1, 2);

    filterLayout->addWidget(makeChanges,        5, 0, 2, 4);

    filterLayout->addWidget(library,            7, 0, 1, 4);
    setLayout(filterLayout);
}

void FilterPage::applyChanges() {
    std::vector<VideoFile> filteredVideos;
    int longerThanUnits = 1;
    int shorterThanUnits = 1;
    if(longerThanCB->currentIndex() == 1) {
        longerThanUnits = 60;
    } else if (longerThanCB->currentIndex() == 2) {
        longerThanUnits = 3600;
    }
    if(shorterThanCB->currentIndex() == 1) {
        shorterThanUnits = 60;
    } else if (shorterThanCB->currentIndex() == 2) {
        shorterThanUnits = 3600;
    }
    for (VideoFile video: allVideos) {
        if (video.hasMeta()) {
            if(video.getDate() > afterDate->date()                        &&
               video.getDate() < beforeDate->date()                       &&
               video.getLen() > longerThanSB->value() * longerThanUnits   &&
               video.getLen() < shorterThanSB->value() * shorterThanUnits &&
               video.getLocation() == locationCB->currentText()             ){
                        filteredVideos.push_back(video);
            }
        }
    }
    library->setVideos(filteredVideos);
}
