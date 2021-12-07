#ifndef RESULTS_H
#define RESULTS_H

#include <QScrollArea>
#include <QLabel>
#include <QtNetwork/QNetworkReply>

// Class containing the results from the map

class Results : public QScrollArea {
public:
    Results();

    void ProcessRequest(QNetworkReply *reply);
};

#endif // RESULTS_H
