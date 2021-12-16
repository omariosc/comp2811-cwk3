#ifndef THE_MAP_PAGE_H
#define THE_MAP_PAGE_H

#include <QResizeEvent>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

#include "Map/image.h"
#include "Map/results.h"
#include "video_file.h"

// Class containing everything for the "Map" page/widget
class MapPage : public QWidget {
  Q_OBJECT
 public:
  MapPage(const std::vector<VideoFile *> &videos, Player *player);

  void resizeEvent(QResizeEvent *e);

  virtual ~MapPage(){};

 private:
  Image *i;
  Results *r;
};

#endif  // THE_MAP_PAGE_H
