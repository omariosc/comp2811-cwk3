#include "filter_page.h"

#include "libraryPage/videolibrary.h"
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>
#include <QDateEdit>
#include <QSpinBox>
#include <QPushButton>


FilterPage::FilterPage(std::vector<VideoFile> &videos, Player *player) : QWidget() {


    QLabel*  afterDateLabel = new QLabel("After date: ");
    afterDateLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    afterDateLabel->setProperty("type", "filterLabel");
    QDateEdit* afterDate = new QDateEdit();

    QLabel* beforeDateLabel = new QLabel("Before date: ");
    beforeDateLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    beforeDateLabel->setProperty("type", "filterLabel");
    QDateEdit* beforeDate = new QDateEdit();

    QStringList units = {"Seconds", "Minutes", "Hours"};

    QLabel* shorterThanLabel = new QLabel("Shorter than: ");
    shorterThanLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    shorterThanLabel->setProperty("type", "filterLabel");
    QSpinBox* shorterThanSB = new QSpinBox();
    shorterThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QComboBox *shorterThanCB = new QComboBox();
    shorterThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    shorterThanCB->addItems(units);


    QLabel* longerThanLabel = new QLabel("Longer than: ");
    longerThanLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    longerThanLabel->setProperty("type", "filterLabel");
    QSpinBox* longerThanSB = new QSpinBox();
    longerThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    QComboBox* longerThanCB = new QComboBox();
    longerThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    longerThanCB->addItems(units);

    QStringList locations = {"LEEDS, UK", "SNOWDON, UK", "PYONGYANG, NK"};
    QLabel* locationLabel = new QLabel("Location: ");
    locationLabel->setAlignment(Qt::AlignRight| Qt::AlignVCenter);
    locationLabel->setProperty("type", "filterLabel");
    locationLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
    QComboBox *locationCB = new QComboBox();
    locationCB->addItems(locations);

    QPushButton* makeChanges = new QPushButton();
    makeChanges->setText("APPLY FILTER");
    makeChanges->setProperty("type", "filter");

    VideoLibrary *library = new VideoLibrary(videos, player);

    QGridLayout *filterLayout = new QGridLayout();
    filterLayout->setColumnStretch(0, 1);
    filterLayout->setColumnStretch(1, 1);
    filterLayout->setColumnStretch(2, 1);
    filterLayout->setColumnStretch(3, 1);

    filterLayout->addWidget(afterDateLabel, 0, 0, 1, 2);
    filterLayout->addWidget(afterDate, 0, 2, 1, 2);

    filterLayout->addWidget(beforeDateLabel, 1, 0, 1, 2);
    filterLayout->addWidget(beforeDate, 1, 2, 1, 2);

    filterLayout->addWidget(shorterThanLabel, 2, 0, 1, 2);
    filterLayout->addWidget(shorterThanSB, 2, 2, 1, 1);
    filterLayout->addWidget(shorterThanCB, 2, 3, 1, 1);

    filterLayout->addWidget(longerThanLabel, 3, 0, 1, 2);
    filterLayout->addWidget(longerThanSB, 3, 2, 1, 1);
    filterLayout->addWidget(longerThanCB, 3, 3, 1, 1);

    filterLayout->addWidget(locationLabel, 4, 0, 1, 2);
    filterLayout->addWidget(locationCB, 4, 2, 1, 2);

    filterLayout->addWidget(makeChanges, 5, 0, 2, 4);

    filterLayout->addWidget(library, 7, 0, 1, 4);
    setLayout(filterLayout);
}
