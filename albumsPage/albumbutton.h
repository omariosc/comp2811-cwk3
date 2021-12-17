#ifndef ALBUMBUTTON_H
#define ALBUMBUTTON_H

#include <QObject>
#include <QToolButton>
#include <QWidget>

class AlbumButton : public QToolButton {
  Q_OBJECT

 public:
  AlbumButton(QWidget* parent);

  void init(int album);
  void setAlbum(int album); //modify the button's albumNr

  virtual ~AlbumButton(){};

 private slots:
  void clicked();

 signals:
  void changeAlbum(int); //Signal an album selection

 private:
  int iconWidth;
  int albumNr; //Holds the album's ID
};

#endif  // ALBUMBUTTON_H
