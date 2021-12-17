#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QtNetwork/QNetworkAccessManager>

#include "results.h"

// Class containing the world map image and processes clicks
class Image : public QLabel {
  Q_OBJECT
public:
  Image();

  void mousePressEvent(QMouseEvent *event) override;
  void resizeEvent(QResizeEvent *e) override;

  void SendRequest(double lat, double lon);
  void ProcessRequest(QNetworkReply *reply);
  void sendRequest(double lat, double lon);
  void processRequest(QNetworkReply *reply);

  virtual ~Image(){};

signals:
  void sendCountry(QString country);

private:
  QNetworkAccessManager *manager;
  QPixmap img;
};
#endif // IMAGE_H
