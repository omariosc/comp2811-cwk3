#ifndef RESULTS_H
#define RESULTS_H

#include <QScrollArea>
#include <QLabel>
#include <QtNetwork/QNetworkReply>

// Class containing the results from the map

class Results : public QScrollArea {
    Q_OBJECT
public:
    Results();

    virtual ~Results() {};

public slots:
    void getCountry(QString country);
};

#endif // RESULTS_H
