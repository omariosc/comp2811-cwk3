#ifndef THE_LIBRARY_PAGE_H
#define THE_LIBRARY_PAGE_H

#include <QWidget>

#include "player.h"
#include "video_file.h"

class LibraryPage : public QWidget {
  Q_OBJECT

 public:
  LibraryPage(std::vector<VideoFile*>& videos, Player* player);
};

#endif  // THE_LIBRARY_PAGE_H
