#ifndef THE_MAP_PAGE_H
#define THE_MAP_PAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QResizeEvent>
#include <vector>

#include "video_file.h"
#include "Map/image.h"
#include "Map/results.h"

// Class containing everything for the "Map" page/widget
class MapPage : public QWidget {
    Q_OBJECT
public:
    MapPage(std::vector<VideoFile> &videos);

    void resizeEvent(QResizeEvent *e);

    virtual ~MapPage() {};

private:
    Image *i;
    Results *r;
};

#endif // THE_MAP_PAGE_H
