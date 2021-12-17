#include "player.h"

#include <QToolButton>

#include "QFile"
#include "QLabel"
#include "QStyle"

static const int butMaxWidth = 360 / 5;
static const int butMinWidth = 50;
static const int butMaxHeight = 25;

Player::Player(VideoFile* video, QStackedWidget* stackedParent)
    : currentVideo(video), stackedParent(stackedParent), isLandscape(false) {
  setWindowTitle("Video Player");
  this->setProperty("type", "menuBackground");
  videoWidget = new QVideoWidget();

  // The QMediaPlayer which controls the playback
  videoPlayer = new VideoPlayer();
  videoPlayer->setVideoOutput(videoWidget);

  // Create the back button
  back = new QToolButton();
  back->setProperty("type", "playerMenu");
  back->setText("Back");
  back->setIcon(QIcon(":/back-white"));
  back->setMaximumWidth(60);

  // Connect it to QStackedWidget
  connect(back, &QToolButton::clicked, this, &Player::quitPlayer);

  // Create the play/pause stacked widget
  QToolButton* play = new QToolButton();
  play->setProperty("type", "playerMenu");
  QToolButton* pause = new QToolButton();
  pause->setProperty("type", "playerMenu");
  play->setIcon(QIcon(":/play-white"));
  pause->setIcon(QIcon(":/pause-white"));
  playPause = new QStackedWidget();
  playPause->addWidget(pause);
  playPause->addWidget(play);
  playPause->setCurrentIndex(0);

  // Connect the play/pause buttons
  connect(play, &QToolButton::clicked, this, &Player::toggleVideo);
  connect(pause, &QToolButton::clicked, this, &Player::toggleVideo);

  // Create the favourite/unfavourite buttons
  favouriteToggle = new QStackedWidget();
  QToolButton* favourite = new QToolButton();
  favourite->setProperty("type", "playerMenu");
  QToolButton* unfavourite = new QToolButton();
  unfavourite->setProperty("type", "playerMenu");
  favourite->setIcon(QIcon(":/hollow-favourite"));
  unfavourite->setIcon(QIcon(":/favouritesIcon"));
  favouriteToggle->addWidget(favourite);
  favouriteToggle->addWidget(unfavourite);
  favouriteToggle->setCurrentIndex(0);

  // And connect them
  connect(favourite, &QToolButton::clicked, this, &Player::toggleFavourite);
  connect(unfavourite, &QToolButton::clicked, this, &Player::toggleFavourite);

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
  toggleRotation->setProperty("type", "playerMenu");
  toggleRotation->setIcon(QIcon(":/rotate-white"));
  connect(toggleRotation, &QToolButton::clicked, this, &Player::rotateScreen);

  // Create the playback speed button
  playbackSpeedButton = new QToolButton();
  playbackSpeedButton->setProperty("type", "playerMenu");
  connect(playbackSpeedButton, &QToolButton::clicked, this,
          &Player::playbackSpeed);
  playbackSpeedButton->setText("Speed");
  playbackSpeedButton->setIcon(QIcon(":/2x-white"));

  // Setting MAXIMUM widths
  // These are the non-stacked buttons
  back->setMaximumHeight(butMaxHeight);
  toggleRotation->setMaximumHeight(butMaxHeight);
  playPause->setMaximumHeight(butMaxHeight);
  favouriteToggle->setMaximumHeight(butMaxHeight);
  playbackSpeedButton->setMaximumHeight(butMaxHeight);
  // These are the QStackedWidgets
  playPause->setMaximumWidth(back->sizeHint().width());
  favouriteToggle->setMaximumWidth(back->sizeHint().width());

  // Setting MINIMUM widths
  back->setMinimumWidth(butMinWidth);
  toggleRotation->setMinimumWidth(butMinWidth);
  playPause->setMinimumWidth(butMinWidth);
  favouriteToggle->setMinimumWidth(butMinWidth);
  playbackSpeedButton->setMinimumWidth(butMinWidth);

  // Setup the layout
  container = new QVBoxLayout();
  container->addWidget(videoWidget, 1);

  QWidget* controls = new QWidget();
  controls->setProperty("type", "playerMenu");

  // Create vertical layout to use within the controls widget
  controlLayout = new QVBoxLayout;
  // And the horizontal layout for the buttons
  buttonLayout = new QHBoxLayout();
  buttonLayout->addWidget(back);
  buttonLayout->addWidget(playPause);
  buttonLayout->addWidget(favouriteToggle);
  buttonLayout->addWidget(toggleRotation);
  buttonLayout->addWidget(playbackSpeedButton);
  // Add the layouts to the controls widget
  controlLayout->addLayout(buttonLayout);
  controls->setLayout(controlLayout);

  // Add the video slider and controls widget to the vertical layout
  container->addWidget(videoSlider);
  container->addWidget(controls);
  container->setContentsMargins(0, 0, 0, 0);
  container->setSpacing(0);
  setLayout(container);

  playVid(video);

  // Ensure original video used for initialization doesn't auto-play
  videoPlayer->pause();
}

void Player::rotateScreen() {
  int width = stackedParent->size().width();
  int height = stackedParent->size().height();

  if (isLandscape) {
    isLandscape = false;
    // Remove the video slider from the horizontal layout with buttons,
    // add it to the vertical layout
    buttonLayout->removeWidget(videoSlider);
    controlLayout->insertWidget(0, videoSlider);
    playPause->setMaximumWidth(butMaxWidth);
    favouriteToggle->setMaximumWidth(butMaxWidth);
  } else {
    isLandscape = true;
    // Same as landscape to portrait, just the reverse
    controlLayout->removeWidget(videoSlider);
    buttonLayout->addWidget(videoSlider);
    playPause->setMaximumWidth(back->sizeHint().width());
    favouriteToggle->setMaximumWidth(back->sizeHint().width());
  }

  stackedParent->resize(height, width);
}

void Player::playVid(VideoFile* newVideo) {
  videoPlayer->pause();
  // Ensure the player is being displayed
  if (stackedParent->currentIndex() != 1) {
    stackedParent->setCurrentIndex(1);
  }

  // Toggle favourite widget if the video is already added to favourites
  if (newVideo->getFavourite()) {
    favouriteToggle->setCurrentIndex(1);
  } else {
    favouriteToggle->setCurrentIndex(0);
  }

  // Since video auto-plays, display the "pause" buttons
  playPause->setCurrentIndex(0);
  videoPlayer->setContent(newVideo);
  currentVideo = newVideo;
  videoPlayer->play();
}

void Player::toggleVideo() {
  int current = playPause->currentIndex();
  if (current == 1) {
    // Play if paused
    videoPlayer->play();
    playPause->setCurrentIndex(0);
  } else {
    // Pause if playing
    videoPlayer->pause();
    playPause->setCurrentIndex(1);
  }
}

void Player::seek(int seconds) { videoPlayer->setPosition(seconds * 1000); }

void Player::playbackSpeed() {
  /*
  Functionality not added due to time constraints
  */
}

void Player::modifySlider(qint64 duration) {
  // Set ticks for each second of the video
  videoSlider->setRange(0, duration / 1000);
}

void Player::updateSlider(qint64 position) {
  if (!videoSlider->isSliderDown()) {
    // Seek to nearest second
    videoSlider->setValue(position / 1000);
  }
}

void Player::toggleFavourite() {
  if (currentVideo->getFavourite() == true) {
    // Unfavourite the video
    currentVideo->setFavourite(false);
    favouriteToggle->setCurrentIndex(0);
  } else {
    // Favourite the video
    currentVideo->setFavourite(true);
    favouriteToggle->setCurrentIndex(1);
  }
}

void Player::quitPlayer() {
  videoPlayer->stop();
  stackedParent->setCurrentIndex(0);  // Display the main UI
  currentVideo = NULL;
  // Emit a signal to announce the player is quiting
  emit playerQuit();
}

void Player::conditionalPlay() {
  // If video was playing before seek, then play it again
  if (playPause->currentIndex() == 0) {
    videoPlayer->play();
  }
}

void Player::playStateChanged(QMediaPlayer::State ms) {
  if (ms == QMediaPlayer::State::StoppedState) {
    videoPlayer->pause();
  }
}

QToolButton* Player::returnBack() { return back; }
