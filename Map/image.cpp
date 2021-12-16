#include "image.h"

Image::Image() {
  img = QPixmap(":world");
  setPixmap(img);

  manager = new QNetworkAccessManager();
}

void Image::mousePressEvent(QMouseEvent *event) {
  // Position of mouse click
  double h = event->y();
  double w = event->x();
  // Dimensions of image
  double th = pixmap()->size().height();
  double tw = pixmap()->size().width();

  // Calculate latitude and logitude
  double lat = 90.0 - ((h / th) * 180.0);
  double lon = ((w / tw) * 360.0) - 170.0;

  sendRequest(lat, lon);
}

void Image::resizeEvent(QResizeEvent *e) {
  double h = e->size().height();
  double w = e->size().width();

  QPixmap scaledImage;

  scaledImage = img.scaled(w, h, Qt::KeepAspectRatio,
                           Qt::TransformationMode::SmoothTransformation);

  // Set label image to new scaled image and set size of label
  setPixmap(scaledImage);
  setFixedSize(scaledImage.size().width(), scaledImage.size().height());
}

void Image::sendRequest(double lat, double lon) {
  auto status = connect(manager, &QNetworkAccessManager::finished, this,
                        &Image::processRequest);

  QString url = QString(
                    "https://nominatim.openstreetmap.org/"
                    "reverse?lat=%1&lon=%2&format=json&zoom=3")
                    .arg(QString::number(lat), QString::number(lon));

  // If you click too quickly it causes a problem with the code waiting for the
  // response - due to usage limits
  manager->get(QNetworkRequest(QUrl(url)));
}

void Image::processRequest(QNetworkReply *reply) {
  QString answer = reply->readAll();

  // Filter out invalid responses
  if (!answer.contains("error") && !answer.isEmpty()) {
    int keyPos = answer.indexOf("country");

    int qPosOne = answer.indexOf("\"", keyPos + 9);
    int qPosTwo = answer.indexOf("\"", qPosOne + 1);

    // Pass country name to results widget
    emit sendCountry(answer.mid(qPosOne + 1, qPosTwo - (qPosOne + 1)));
  }
}
