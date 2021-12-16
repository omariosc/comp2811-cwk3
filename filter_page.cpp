#include "filter_page.h"

#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>

#include "libraryPage/videolibrary.h"

FilterPage::FilterPage(std::vector<VideoFile *> &videos, Player *player)
    : QWidget() {
  allVideos = videos;
  mediaPlayer = player;

  afterDate = new QCheckBox("After date: ");
  afterDate->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
  afterDate->setProperty("type", "filter");
  afterDateDE = new QDateEdit();

  beforeDate = new QCheckBox("Before date: ");
  beforeDate->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
  beforeDate->setProperty("type", "filter");
  beforeDateDE = new QDateEdit();

  QStringList units = {"Seconds", "Minutes", "Hours"};

  longerThan = new QCheckBox("Longer than: ");
  longerThan->setProperty("type", "filter");
  longerThan->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
  longerThanSB = new QSpinBox();
  longerThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  longerThanCB = new QComboBox();
  longerThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  longerThanCB->addItems(units);

  shorterThan = new QCheckBox("Shorter than: ");
  shorterThan->setProperty("type", "filter");
  shorterThan->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
  shorterThanSB = new QSpinBox();
  shorterThanSB->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
  shorterThanCB = new QComboBox();
  shorterThanCB->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  shorterThanCB->addItems(units);

  QStringList locations = {"LEEDS, UK", "SNOWDON, UK", "PYONGYANG, NK",
                           "WASHINGTON, US"};
  location = new QCheckBox("Location: ");
  location->setProperty("type", "filter");
  location->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Ignored);
  locationCB = new QComboBox();
  locationCB->addItems(locations);

  QPushButton *makeChanges = new QPushButton();
  makeChanges->setText("APPLY FILTER");
  makeChanges->setProperty("type", "filter");
  connect(makeChanges, &QPushButton::clicked, this, &FilterPage::applyChanges);

  library = new VideoLibrary(videos, mediaPlayer);

  QGridLayout *filterLayout = new QGridLayout();
  filterLayout->setHorizontalSpacing(0);
  filterLayout->setColumnStretch(0, 1);
  filterLayout->setColumnStretch(1, 1);
  filterLayout->setColumnStretch(2, 1);
  filterLayout->setColumnStretch(3, 1);

  filterLayout->addWidget(afterDate, 0, 0, 1, 2);
  filterLayout->addWidget(afterDateDE, 0, 2, 1, 2);

  filterLayout->addWidget(beforeDate, 1, 0, 1, 2);
  filterLayout->addWidget(beforeDateDE, 1, 2, 1, 2);

  filterLayout->addWidget(longerThan, 2, 0, 1, 2);
  filterLayout->addWidget(longerThanSB, 2, 2, 1, 1);
  filterLayout->addWidget(longerThanCB, 2, 3, 1, 1);

  filterLayout->addWidget(shorterThan, 3, 0, 1, 2);
  filterLayout->addWidget(shorterThanSB, 3, 2, 1, 1);
  filterLayout->addWidget(shorterThanCB, 3, 3, 1, 1);

  filterLayout->addWidget(location, 4, 0, 1, 2);
  filterLayout->addWidget(locationCB, 4, 2, 1, 2);

  filterLayout->addWidget(makeChanges, 5, 0, 2, 4);

  filterLayout->addWidget(library, 7, 0, 1, 4);
  setLayout(filterLayout);
}

void FilterPage::applyChanges() {
  std::vector<VideoFile *> filteredVideos;
  int longerThanUnits = 1;
  int shorterThanUnits = 1;
  if (longerThanCB->currentIndex() == 1) {
    longerThanUnits = 60;
  } else if (longerThanCB->currentIndex() == 2) {
    longerThanUnits = 3600;
  }
  if (shorterThanCB->currentIndex() == 1) {
    shorterThanUnits = 60;
  } else if (shorterThanCB->currentIndex() == 2) {
    shorterThanUnits = 3600;
  }
  for (VideoFile *video : allVideos) {
    if (video->hasMeta()) {
      bool valid = true;
      if (afterDate->isChecked()) {
        if (video->getDate() <= afterDateDE->date()) {
          valid = false;
        }
      }
      if (beforeDate->isChecked()) {
        if (video->getDate() >= afterDateDE->date()) {
          valid = false;
        }
      }
      if (longerThan->isChecked()) {
        if (video->getLen() <= longerThanSB->value() * longerThanUnits) {
          valid = false;
        }
      }
      if (shorterThan->isChecked()) {
        if (video->getLen() >= shorterThanSB->value() * shorterThanUnits) {
          valid = false;
        }
      }
      if (location->isChecked()) {
        if (video->getLocation() != locationCB->currentText()) {
          valid = false;
        }
      }
      if (valid) {
        filteredVideos.push_back(video);
      }
    }
  }
  library->changeVideos(filteredVideos);
}
