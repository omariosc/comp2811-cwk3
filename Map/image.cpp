#include "image.h"

Image::Image() {
    img = QPixmap(":/world.jpg");
    setPixmap(img);

    manager = new QNetworkAccessManager();
}

void Image::mousePressEvent(QMouseEvent *event) {
    qDebug() << event->x();
    qDebug() << event->y();
    qDebug() << pixmap()->size().height();
    qDebug() << pixmap()->size().width();

    SendRequest(54.12345, -1.12345);
}

void Image::resizeEvent(QResizeEvent *e) {
    int w = e->size().width();
    int h = e->size().height();

    qDebug() << "HERE";

    setPixmap(img.scaled(w, h, Qt::KeepAspectRatio));
}

void Image::SendRequest(double lat, double lon) {
    auto status = connect(manager, &QNetworkAccessManager::finished, this, &Results::ProcessRequest);
    qDebug() << "Connection status:" << status;

    QString url = QString("https://nominatim.openstreetmap.org/reverse?lat=%1&lon=%2&format=json&zoom=3").arg(QString::number(lat), QString::number(lon));

    manager->get(QNetworkRequest(QUrl(url)));
}
