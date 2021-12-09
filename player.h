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
    Player(std::vector<VideoFile> videos,QStackedWidget* toggler);
    void playVideo();

public slots:
    void playVideo(VideoFile* newVideo);
    void quitPlayer();

private slots:
    void toggleVideo();
    void seek(int seconds);
    void modifySlider(qint64 duration);
    void updateSlider(qint64 position);
    void toggleFavorite();

private:
    VideoFile* currentVideo;
    QStackedWidget *playPause;
    VideoPlayer *player;
    QSlider *videoSlider;
    QStackedWidget* toggler;
};

#endif // PLAYER_H
