#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include "video_player.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "video_file.h"
#include <QtMultimediaWidgets/QVideoWidget>
#include <QStackedWidget>
#include <QSlider>

class Player: public QWidget{
    Q_OBJECT
public:
    Player(VideoFile* video,QStackedWidget* toggler);
    void playVideo();
    void setScreen();

public slots:
    void playVideo(VideoFile* newVideo);
    void quitPlayer();
    void rotateScreen();

private slots:
    void toggleVideo();
    void seek(int seconds);
    void modifySlider(qint64 duration);
    void updateSlider(qint64 position);
    void toggleFavorite();
    void conditionalPlay();

private:
    VideoFile* currentVideo;
    QStackedWidget *playPause;
    VideoPlayer *player;
    QSlider *videoSlider;
    QStackedWidget* toggler;
    QVideoWidget* videoWidget;
    QPushButton* favorite;
    QPushButton* toggleRotation;
    QPushButton* back;
    QHBoxLayout* bot;
    QVBoxLayout* top;
    bool isLandscape;
};

#endif // PLAYER_H
