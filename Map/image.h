#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include <QtNetwork/QNetworkAccessManager>
#include <QMouseEvent>
#include <QResizeEvent>

#include "results.h"

// Class containing the world map image and processes clicks

class Image : public QLabel {
public:
    Image();

    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *e) override;

    void SendRequest(double lat, double lon);
    void ProcessRequest(QNetworkReply *reply);

private:
    QNetworkAccessManager *manager;

    QPixmap img;
};

#endif // IMAGE_H
