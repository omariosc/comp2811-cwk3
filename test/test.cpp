#include <iostream>
#include "test.h"

MyObject::MyObject(QApplication* app) {
    manager = new QNetworkAccessManager(app);
}

void MyObject::TestConnection() const {
    auto status = connect(manager, &QNetworkAccessManager::finished, this, &MyObject::ReplyFinished);
    qDebug() << "Connection status:" << status;

    manager->get(QNetworkRequest(QUrl("https://nominatim.openstreetmap.org/reverse?lat=53.794812445781105&lon=-1.505817435048274&format=json&zoom=3")));
}

void MyObject::ReplyFinished(QNetworkReply *reply) {
    QString answer = reply->readAll();
    qDebug() << answer;
    QApplication::quit();
}

int main(int argc, char *argv[]) {
    auto *app = new QApplication(argc, argv);
    auto myObject = new MyObject(app);
    myObject->TestConnection();
    return QApplication::exec();
}
