#ifndef RESULTS_H
#define RESULTS_H

#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QtNetwork/QNetworkReply>
#include <algorithm>
#include <random>

#include "../libraryPage/videolibrary.h"
#include "../video_file.h"

// Class containing the results from the map
class Results : public QWidget {
  Q_OBJECT
 public:
  Results(const std::vector<VideoFile *> &videos, Player *player);

  virtual ~Results(){};

  void refresh();

 public slots:
  void getCountry(QString country);

 private:
  void updateWidget(QString country);

  QLabel *header;
  VideoLibrary *result;

  std::vector<VideoFile *> v;
  Player *p;
};

#endif  // RESULTS_H
