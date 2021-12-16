#ifndef ALBUMBUTTON_H
#define ALBUMBUTTON_H

#include <QObject>
#include <QWidget>
#include <QToolButton>

class AlbumButton: public QToolButton
{
    Q_OBJECT

public:

    AlbumButton(QWidget* parent);

    void init(int album);
    void setAlbum(int album);

    virtual ~AlbumButton() {};

private slots:
    void clicked();

signals:
    void changeAlbum(int);

private:
    int iconWidth;
    int albumNr;
};

#endif // ALBUMBUTTON_H
