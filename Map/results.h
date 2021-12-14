#ifndef RESULTS_H
#define RESULTS_H

#include <QScrollArea>
#include <QLabel>
#include <QtNetwork/QNetworkReply>
#include <QVBoxLayout>
#include <QGridLayout>

// Class containing the results from the map

class Results : public QWidget {
    Q_OBJECT
public:
    Results();

    virtual ~Results() {};

public slots:
    void getCountry(QString country);

private:
    void updateWidget(QString country);

    QLabel *header;
    QWidget *results;
};

#endif // RESULTS_H
