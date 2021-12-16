#include "image.h"

Image::Image() {
    img = QPixmap(":/resources/world.jpg");
    setPixmap(img);

    manager = new QNetworkAccessManager();
}

void Image::mousePressEvent(QMouseEvent *event) {
    double h = event->y();
    double w = event->x();
    double th = pixmap()->size().height();
    double tw = pixmap()->size().width();

    double lat = 90.0-((h/th)*180.0);
    double lon = ((w/tw)*360.0)-170.0;

    sendRequest(lat, lon);
}

void Image::resizeEvent(QResizeEvent *e) {
    double h = e->size().height();
    double w = e->size().width();

    QPixmap scaledImage;

    scaledImage = img.scaled(w, h, Qt::KeepAspectRatio, Qt::TransformationMode::SmoothTransformation);

    setPixmap(scaledImage);
    setFixedSize(scaledImage.size().width(), scaledImage.size().height());
}

void Image::sendRequest(double lat, double lon) {
    auto status = connect(manager, &QNetworkAccessManager::finished, this, &Image::processRequest);

    QString url = QString("https://nominatim.openstreetmap.org/reverse?lat=%1&lon=%2&format=json&zoom=3").arg(QString::number(lat), QString::number(lon));

    // If you click too quickly it causes a problem with the code waiting for the response - due to usage limits
    manager->get(QNetworkRequest(QUrl(url)));
}

void Image::processRequest(QNetworkReply *reply) {
    QString answer = reply->readAll();

    if (!answer.contains("error") && !answer.isEmpty()) {
        int keyPos = answer.indexOf("country");

        int qPosOne = answer.indexOf("\"", keyPos+9);
        int qPosTwo = answer.indexOf("\"", qPosOne+1);

        emit sendCountry(answer.mid(qPosOne+1, qPosTwo - (qPosOne+1)));
    }
}
