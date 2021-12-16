#ifndef ALBUMBUTTON_H
#define ALBUMBUTTON_H

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <albumsPage/albumbutton.h>

class AlbumButton: public QToolButton
{
public:

    AlbumButton(QWidget* parent);

    void init(int album);

private slots:
    void clicked();

signals:
    void changeAlbum(int);

private:
    int iconWidth;
    int albumNr;
};

#endif // ALBUMBUTTON_H
