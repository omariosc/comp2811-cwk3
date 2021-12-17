#ifndef THE_FILTER_PAGE_H
#define THE_FILTER_PAGE_H

#include <QCheckBox>
#include <QComboBox>
#include <QDateEdit>
#include <QSpinBox>
#include <QWidget>

#include "libraryPage/videolibrary.h"
#include "player.h"
#include "video_file.h"

class FilterPage : public QWidget {
  Q_OBJECT

 public:
  FilterPage(std::vector<VideoFile*>& videos, Player* player);

 public slots:
  void refresh(); // Refresh library

 private slots:
  void applyChanges(); // Changes results based on filters chosen

 private:
  std::vector<VideoFile*> allVideos; // All videos that can be filtered through, should be set in constructor
  Player* mediaPlayer; // Player to link to
  QCheckBox* afterDate; // Toggle of filter including videos after given date
  QDateEdit* afterDateDE;
  QCheckBox* beforeDate; // Toggle of filter including videos before given date
  QDateEdit* beforeDateDE;
  QCheckBox* longerThan; // Toggle of filter including videos longer than a given amount of time
  QSpinBox* longerThanSB;
  QComboBox* longerThanCB; // Options of time units
  QCheckBox* shorterThan; // Toggle of filter including videos shorter than a given amount of time
  QSpinBox* shorterThanSB;
  QComboBox* shorterThanCB; // Options of time units
  QCheckBox* location; // Toggle of filter including videos from set location
  QComboBox* locationCB; // Options of locations
  VideoLibrary* library; // Results display
};

#endif  // THE_FILTER_PAGE_H
