#include "video_file.h"
#include "QPainter"
#include "qdebug.h"


VideoFile::VideoFile( QUrl* url, QIcon* icon, bool favorite) : url (url), favorite(favorite) {
    setIcon(icon);
}

void VideoFile::setIcon(QIcon* newIcon){
    if(favorite) {
        qDebug() << "It's a favourite!";
        QPixmap base, overlay; // come from your code
        base = newIcon->pixmap(128,128);
        overlay = QPixmap(":/favouritesOverlay");
        QPixmap result(base.width(), base.height());
        result.fill(Qt::transparent); // force alpha channel
        QPainter painter(&result);
        painter.drawPixmap(0, 0, base);
        painter.drawPixmap(0, 0, overlay);
        icon = new QIcon(result);
    }
    else{
        icon = newIcon;
    }
}

void VideoFile::setFavourite(bool flag){
    favorite = flag;
    setIcon(icon);
}

bool VideoFile::getFavourite(){
    return favorite;
}
