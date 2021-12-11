#include "player.h"
#include "QLabel"
#include "QStyle"
#include "QFile"

//static const int buttonWidth = 30;
static const int butMaxWidth = 50;

Player::Player(VideoFile* video,QStackedWidget* toggler): currentVideo(video), toggler(toggler), isLandscape(true)
{
    this->setMinimumSize(100,100);
    setWindowTitle("Video Player");

    QFile File(":/tomeoStyleSheet");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());
    setStyleSheet(StyleSheet);

    videoWidget = new QVideoWidget();
    videoWidget->setMinimumSize(100,100);

    // the QMediaPlayer which controls the playback
    player = new VideoPlayer();
    player->setVideoOutput(videoWidget);

    //Create the back button
    back = new QPushButton();
    back->setText("Back");
    back->setMaximumWidth(butMaxWidth);

    //Connect it to QStackedWidget
    connect(back,&QPushButton::clicked,this,&Player::quitPlayer);


    //Create the play/pause stacked widget
    QPushButton *play = new QPushButton();
    QPushButton *pause = new QPushButton();
    play->setText("&Play");
    pause->setText("&Pause");
    playPause = new QStackedWidget();
    playPause->setMaximumHeight(back->sizeHint().height());
    playPause->setMaximumWidth(butMaxWidth);
    playPause->addWidget(pause);
    playPause->addWidget(play);
    playPause->setCurrentIndex(1);
//    playPause->setMinimumHeight(30);

    //Connect the play/pause buttons
    connect(play,SIGNAL(clicked()),this,SLOT(toggleVideo()));
    connect(pause,SIGNAL(clicked()),this,SLOT(toggleVideo()));

    //Create the "favorite" button
    favorite = new QPushButton();
    favorite->setText("Fav");
    favorite->setMaximumWidth(butMaxWidth);

    //And connect it
    connect(favorite,&QPushButton::clicked,this,&Player::toggleFavorite);

    //Make the scroll and add it
    videoSlider = new QSlider(Qt::Horizontal,this);
    qDebug() << "Video duration: " << player->duration();
    videoSlider->setRange(0, player->duration());
    videoSlider->setMinimumWidth(20);

    //Connect scroll to VideoPlayer
    connect(videoSlider, &QSlider::sliderMoved, this, &Player::seek);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::modifySlider);
    connect(player,&QMediaPlayer::positionChanged,this,&Player::updateSlider);
    connect(videoSlider,&QSlider::sliderPressed,player,&QMediaPlayer::pause);
    connect(videoSlider,&QSlider::sliderReleased,this,&Player::conditionalPlay);

    //Create rotation toggle button
    toggleRotation = new QPushButton();
    connect(toggleRotation,&QPushButton::clicked,this,&Player::rotateScreen);
    toggleRotation->setMaximumWidth(butMaxWidth);
    toggleRotation->setText("Rotate");

    //setup the layout
    top = new QVBoxLayout();
    top->addWidget(videoWidget);

    bot = new QHBoxLayout();
    bot->addWidget(back);
    bot->addWidget(playPause);
    bot->addWidget(favorite);
    bot->addWidget(toggleRotation);
    //bot->addWidget(new QLabel("Seeker:"));
    bot->addWidget(videoSlider);

    top->addLayout(bot);
    top->setContentsMargins(0,0,0,0);
    isLandscape = true;
    setLayout(top);
    //layout()->update();
    show();

    playVideo(video);
    player->pause();
}

void Player::rotateScreen(){

    if(isLandscape == true){
        isLandscape = false;
        bot->removeWidget(videoSlider);
        top->insertWidget(1,videoSlider);
    }
    else{
        isLandscape = true;
        top->removeWidget(videoSlider);
        bot->addWidget(videoSlider);
    }
}

void Player::playVideo(VideoFile* newVideo){
    player->pause();
    if(toggler->currentIndex() != 1) toggler->setCurrentIndex(1);
    playPause->setCurrentIndex(1);
    player->setContent(newVideo);
    currentVideo = newVideo;
    player->pause();
    show();
}

void Player::toggleVideo(){
    int current = playPause->currentIndex();
    if(current == 1){
        qDebug() << "Playing Video";
        player->play();
        playPause->setCurrentIndex(0);
    }
    else{
        qDebug() << "Pausing Video";
        player->pause();
        playPause->setCurrentIndex(1);
    }
}

void Player::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

void Player::modifySlider(qint64 duration){
    videoSlider->setRange(0,duration/1000);
}

void Player::updateSlider(qint64 position){
    if (!videoSlider->isSliderDown())
        videoSlider->setValue(position / 1000);
}

void Player::toggleFavorite(){
    if(currentVideo->favorite == true){
        currentVideo->favorite = false;
        qDebug() << "Video removed from favorites";
    }
    else{
        currentVideo->favorite = true;
        qDebug() << "Video added to favorites";
    }
}

void Player::quitPlayer(){
    player->stop();
    toggler->setCurrentIndex(0);
    currentVideo = NULL;
}

void Player::conditionalPlay(){
    if(playPause->currentIndex() == 0) player->play();
}
