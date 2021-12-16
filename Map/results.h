#ifndef RESULTS_H
#define RESULTS_H

#include <QScrollArea>
#include <QLabel>
#include <QtNetwork/QNetworkReply>
#include <QVBoxLayout>
#include <QGridLayout>

#include <random>
#include <algorithm>

#include "../video_file.h"
#include "../libraryPage/videolibrary.h"

// Class containing the results from the map
class Results : public QWidget {
    Q_OBJECT
public:
    Results(const std::vector<VideoFile*> &videos, Player* player);

    virtual ~Results() {};

public slots:
    void getCountry(QString country);

private:
    void updateWidget(QString country);

    QLabel *header;
    QWidget *results;

    std::vector<VideoFile*> v;
    Player* p;
};

#endif // RESULTS_H
