#include "video_file.h"
#include "QPainter"
#include "qdebug.h"


VideoFile::VideoFile( QUrl* url, QIcon* icon, bool favorite) : url (url), originalIcon (icon), favorite(favorite) {
    updateIcon();
}

void VideoFile::updateIcon(QIcon* newIcon){
    if(newIcon) {
        originalIcon = newIcon;
    }
    newIcon = originalIcon;
    if(favorite) {
        qDebug() << "It's a favourite!";
        QPixmap base, overlay;
        base = newIcon->pixmap(128,128);
        overlay = QPixmap(":/favouritesOverlay");
        QPixmap result(base.width(), base.height());
        result.fill(Qt::transparent);
        QPainter painter(&result);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(0, 0, overlay);
        icon = QIcon(result);
    }
    else{
        icon = *newIcon;
    }
}

void VideoFile::setFavourite(bool flag){
    favorite = flag;
    updateIcon();
}

void VideoFile::toggleFavourite(){
    favorite = !favorite;
    updateIcon();
}

bool VideoFile::getFavourite(){
    return favorite;
}