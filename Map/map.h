#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QVBoxLayout>

#include "image.h"
#include "results.h"

// Class containing everything for the "Map" page/widget

class Map : public QWidget {
    Q_OBJECT
public:
    Map();

    virtual ~Map() {};
};

#endif // MAP_H
