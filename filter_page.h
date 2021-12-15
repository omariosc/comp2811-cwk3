#ifndef THE_FILTER_PAGE_H
#define THE_FILTER_PAGE_H

#include <QWidget>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include "video_file.h"
#include "player.h"
#include "libraryPage/videolibrary.h"

class FilterPage : public QWidget {
    Q_OBJECT

public:
    FilterPage(std::vector<VideoFile> &videos, Player* player);

private slots:
    void applyChanges();

private:
    std::vector<VideoFile> allVideos;
    Player* mediaPlayer;
    QDateEdit* afterDate;
    QDateEdit* beforeDate;
    QSpinBox* longerThanSB;
    QComboBox* longerThanCB;
    QSpinBox* shorterThanSB;
    QComboBox* shorterThanCB;
    QComboBox* locationCB;
    VideoLibrary *library;



};

#endif // THE_FILTER_PAGE_H     
