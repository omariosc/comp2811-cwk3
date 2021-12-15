#ifndef THE_FILTER_PAGE_H
#define THE_FILTER_PAGE_H

#include <QWidget>
#include <QDateEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
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
    VideoLibrary *library;
};

#endif // THE_FILTER_PAGE_H     
