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
  void refresh();

 private slots:
  void applyChanges();

 private:
  std::vector<VideoFile*> allVideos;
  Player* mediaPlayer;
  QCheckBox* afterDate;
  QDateEdit* afterDateDE;
  QCheckBox* beforeDate;
  QDateEdit* beforeDateDE;
  QCheckBox* longerThan;
  QSpinBox* longerThanSB;
  QComboBox* longerThanCB;
  QCheckBox* shorterThan;
  QSpinBox* shorterThanSB;
  QComboBox* shorterThanCB;
  QCheckBox* location;
  QComboBox* locationCB;
  VideoLibrary* library;
};

#endif  // THE_FILTER_PAGE_H
