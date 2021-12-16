#include "player.h"

#include <QToolButton>

#include "QFile"
#include "QLabel"
#include "QStyle"

static const int butMaxWidth = 360 / 5;
static const int butMinWidth = 50;
static const int butMaxHeight = 25;

Player::Player(VideoFile* video, QStackedWidget* toggler)
    : currentVideo(video), toggler(toggler), isLandscape(false) {
  setWindowTitle("Video Player");
  this->setProperty("type", "menuBackground");
  setStyleSheet(
      "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 "
      "#191919, stop: 0.4 #2D2D2D, stop: 0.5 #2D2D2D, stop: 1.0 #191919);");
  videoWidget = new QVideoWidget();

  // The QMediaPlayer which controls the playback
  videoPlayer = new VideoPlayer();
  videoPlayer->setVideoOutput(videoWidget);

  // Create the back button
  back = new QToolButton();
  back->setText("Back");
  back->setIcon(QIcon(":/back-white"));
  back->setMaximumWidth(60);

  // Connect it to QStackedWidget
  connect(back, &QToolButton::clicked, this, &Player::quitPlayer);

  // Create the play/pause stacked widget
  QToolButton* play = new QToolButton();
  QToolButton* pause = new QToolButton();
  play->setIcon(QIcon(":/play-white"));
  pause->setIcon(QIcon(":/pause-white"));
  playPause = new QStackedWidget();
  playPause->addWidget(pause);
  playPause->addWidget(play);
  playPause->setCurrentIndex(0);

  // Connect the play/pause buttons
  connect(play, &QToolButton::clicked, this, &Player::toggleVideo);
  connect(pause, &QToolButton::clicked, this, &Player::toggleVideo);

  // Create the favorite/unfavorite buttons
  favoriteToggle = new QStackedWidget();
  QToolButton* favorite = new QToolButton();
  QToolButton* unfavorite = new QToolButton();
  favorite->setIcon(QIcon(":/hollow-favourite"));
  unfavorite->setIcon(QIcon(":/favouritesIcon"));
  favoriteToggle->addWidget(favorite);
  favoriteToggle->addWidget(unfavorite);
  favoriteToggle->setCurrentIndex(0);

  // And connect them
  connect(favorite, &QToolButton::clicked, this, &Player::toggleFavorite);
  connect(unfavorite, &QToolButton::clicked, this, &Player::toggleFavorite);

  // Make the scroll and add it
  videoSlider = new QSlider(Qt::Horizontal, this);
  videoSlider->setRange(0, videoPlayer->duration());
  videoSlider->setMinimumWidth(20);

  // Connect scroll to VideoPlayer
  connect(videoSlider, &QSlider::sliderMoved, this, &Player::seek);
  connect(videoSlider, &QSlider::sliderPressed, videoPlayer,
          &QMediaPlayer::pause);
  connect(videoSlider, &QSlider::sliderReleased, this,
          &Player::conditionalPlay);
  connect(videoPlayer, &QMediaPlayer::durationChanged, this,
          &Player::modifySlider);
  connect(videoPlayer, &QMediaPlayer::positionChanged, this,
          &Player::updateSlider);

  // Create rotation toggle button
  toggleRotation = new QToolButton();
  toggleRotation->setIcon(QIcon(":/rotate-white"));
  connect(toggleRotation, &QToolButton::clicked, this, &Player::rotateScreen);

  // Code here kept in case we decide to add the "playback" button back
  // Create the playback speed button
  playbackSpeedButton = new QToolButton();
  connect(playbackSpeedButton, &QToolButton::clicked, this,
          &Player::playbackSpeed);
  playbackSpeedButton->setText("Speed");
  playbackSpeedButton->setIcon(QIcon(":/2x-white"));

  // Setting MAXIMUM widths
  // These are the non-stacked buttons
  back->setMaximumHeight(butMaxHeight);
  toggleRotation->setMaximumHeight(butMaxHeight);
  playPause->setMaximumHeight(butMaxHeight);
  favoriteToggle->setMaximumHeight(butMaxHeight);
  playbackSpeedButton->setMaximumHeight(butMaxHeight);
  // These are the QStackedWidgets
  playPause->setMaximumWidth(back->sizeHint().width());
  favoriteToggle->setMaximumWidth(back->sizeHint().width());

  // Setting MINIMUM widths
  back->setMinimumWidth(butMinWidth);
  toggleRotation->setMinimumWidth(butMinWidth);
  playPause->setMinimumWidth(butMinWidth);
  favoriteToggle->setMinimumWidth(butMinWidth);
  playbackSpeedButton->setMinimumWidth(butMinWidth);

  // Setup the layout
  top = new QVBoxLayout();
  top->addWidget(videoWidget);

  QWidget* bot = new QWidget();
  bot->setStyleSheet("background: #5c6670;");
  bot->setStyleSheet(
      "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #191919, "
      "stop: 0.4 #2D2D2D,stop: 0.5 #2D2D2D, stop: 1.0 #191919);");

  bottoplayout = new QVBoxLayout;
  botlayout = new QHBoxLayout();
  botlayout->addWidget(back);
  botlayout->addWidget(playPause);
  botlayout->addWidget(favoriteToggle);
  botlayout->addWidget(toggleRotation);
  botlayout->addWidget(playbackSpeedButton);
  bottoplayout->addLayout(botlayout);
  bot->setLayout(bottoplayout);

  top->addWidget(videoSlider);
  top->addWidget(bot);
  top->setContentsMargins(0, 0, 0, 0);
  top->setSpacing(0);
  setLayout(top);
  show();

  playVideo(video);
  QFile File(":/tomeoStyleSheet");
  File.open(QFile::ReadOnly);
  QString StyleSheet = QLatin1String(File.readAll());
  setStyleSheet(StyleSheet);
  videoPlayer->pause();
}

void Player::rotateScreen() {
  int width = toggler->size().width();
  int height = toggler->size().height();

  if (isLandscape == true) {
    isLandscape = false;
    botlayout->removeWidget(videoSlider);
    bottoplayout->insertWidget(0, videoSlider);
    playPause->setMaximumWidth(butMaxWidth);
    favoriteToggle->setMaximumWidth(butMaxWidth);
  } else {
    isLandscape = true;
    bottoplayout->removeWidget(videoSlider);
    botlayout->addWidget(videoSlider);
    playPause->setMaximumWidth(back->sizeHint().width());
    favoriteToggle->setMaximumWidth(back->sizeHint().width());
  }

  toggler->resize(height, width);
}

void Player::playVideo(VideoFile* newVideo) {
  videoPlayer->pause();
  if (toggler->currentIndex() != 1) toggler->setCurrentIndex(1);
  if (newVideo->getFavourite() == true)
    favoriteToggle->setCurrentIndex(1);
  else
    favoriteToggle->setCurrentIndex(0);
  playPause->setCurrentIndex(0);
  videoPlayer->setContent(newVideo);
  currentVideo = newVideo;
  videoPlayer->play();
  show();
}

void Player::toggleVideo() {
  int current = playPause->currentIndex();
  if (current == 1) {
    videoPlayer->play();
    playPause->setCurrentIndex(0);
  } else {
    videoPlayer->pause();
    playPause->setCurrentIndex(1);
  }
}

void Player::seek(int seconds) { videoPlayer->setPosition(seconds * 1000); }

void Player::playbackSpeed() {
  /*
  Function added if time allows for an implementation later on.
  It will be removed if it can not be implemented by the final iteration
  */
}

void Player::modifySlider(qint64 duration) {
  videoSlider->setRange(0, duration / 1000);
}

void Player::updateSlider(qint64 position) {
  if (!videoSlider->isSliderDown()) videoSlider->setValue(position / 1000);
}

void Player::toggleFavorite() {
  if (currentVideo->getFavourite() == true) {
    currentVideo->setFavourite(false);
    favoriteToggle->setCurrentIndex(0);
  } else {
    currentVideo->setFavourite(true);
    favoriteToggle->setCurrentIndex(1);
  }
}

void Player::quitPlayer() {
  videoPlayer->stop();
  toggler->setCurrentIndex(0);
  currentVideo = NULL;
  emit playerQuit();
}

void Player::conditionalPlay() {
  if (playPause->currentIndex() == 0) videoPlayer->play();
}

QToolButton* Player::returnBack() { return back; }
