#ifndef THE_FILTER_PAGE_H
#define THE_FILTER_PAGE_H

#include <QWidget>
#include "video_file.h"

class FilterPage : public QWidget {
    Q_OBJECT

public:
    FilterPage(std::vector<VideoFile> &videos) : QWidget() {}

};

#endif // THE_FILTER_PAGE_H
