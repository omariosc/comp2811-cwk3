#include "image.h"

Image::Image() {
    img = QPixmap(":/world.jpg");
    setPixmap(img);

    manager = new QNetworkAccessManager();
}

void Image::mousePressEvent(QMouseEvent *event) {
    double h = event->y();
    double w = event->x();
    double th = pixmap()->size().height();
    double tw = pixmap()->size().width();

    qDebug() << h;
    qDebug() << th;

    qDebug() << w;
    qDebug() << tw;

    double lat = 90.0-((h/th)*180.0);
    double lon = ((w/tw)*360.0)-170.0;

    SendRequest(lat, lon);
}

void Image::resizeEvent(QResizeEvent *e) {
    int h = e->size().height();

    setPixmap(img.scaledToHeight(h, Qt::TransformationMode::SmoothTransformation));
}

void Image::SendRequest(double lat, double lon) {
    qDebug() << lat;
    qDebug() << lon;
    auto status = connect(manager, &QNetworkAccessManager::finished, this, &Image::ProcessRequest);

    QString url = QString("https://nominatim.openstreetmap.org/reverse?lat=%1&lon=%2&format=json&zoom=3").arg(QString::number(lat), QString::number(lon));

    manager->get(QNetworkRequest(QUrl(url)));
}

void Image::ProcessRequest(QNetworkReply *reply) {
    QString answer = reply->readAll();
    qDebug() << answer;
}
