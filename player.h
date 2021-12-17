//
// Created by twak on 11/11/2019.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <QSlider>
#include <QStackedWidget>
#include <QToolButton>
#include <QWidget>
#include <QtMultimediaWidgets/QVideoWidget>

#include "QHBoxLayout"
#include "QVBoxLayout"
#include "video_file.h"
#include "video_player.h"

class Player : public QWidget {
  Q_OBJECT
 public:
  Player(VideoFile* video, QStackedWidget* toggler);
  void playVideo();
  void setScreen();
  QToolButton* returnBack();

 signals:
  void playerQuit();

 public slots:
  void playVid(VideoFile* newVideo);
  void quitPlayer();
  void rotateScreen();

 private slots:
  void toggleVideo();
  void seek(int seconds);
  void modifySlider(qint64 duration);
  void updateSlider(qint64 position);
  void toggleFavorite();
  void conditionalPlay();
  void playbackSpeed();
  void playStateChanged (QMediaPlayer::State ms);

 private:
  VideoFile* currentVideo;
  QStackedWidget* playPause;
  VideoPlayer* videoPlayer;
  QSlider* videoSlider;
  QStackedWidget* toggler;
  QVideoWidget* videoWidget;
  QStackedWidget* favoriteToggle;
  QToolButton* toggleRotation;
  QToolButton* playbackSpeedButton;
  QToolButton* back;
  QHBoxLayout* botlayout;
  QVBoxLayout* top;
  QVBoxLayout* bottoplayout;
  bool isLandscape;
  qreal playback;
};

#endif  // PLAYER_H
