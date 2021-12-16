#ifndef THE_MAP_PAGE_H
#define THE_MAP_PAGE_H

#include <QWidget>
#include "video_file.h"

class MapPage : public QWidget {
    Q_OBJECT

public:
    MapPage(std::vector<VideoFile*> &videos) : QWidget() {}

};

#endif // THE_MAP_PAGE_H
