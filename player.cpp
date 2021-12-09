#include "player.h"
#include "QLabel"

static const int buttonWidth = 30;

Player::Player(std::vector<VideoFile> videos)
{
    this->setMinimumSize(320,320);

    QVideoWidget *videoWidget = new QVideoWidget();
    videoWidget->setMinimumSize(300,300);

    // the QMediaPlayer which controls the playback
    player = new VideoPlayer();
    player->setVideoOutput(videoWidget);

    // tell the player what buttons and videos are available
    player->setContent(&videos[0]);
    //player->setContent(NULL);

    // create the main window and layout
    QVBoxLayout *top = new QVBoxLayout();
    setLayout(top);
    setWindowTitle("Video Player");

    // add the video and the buttons
    top->addWidget(videoWidget);


    //Create the button layout
    QHBoxLayout *bot = new QHBoxLayout();

    //Create the play/pause stacked widget
    QPushButton *play = new QPushButton();
    QPushButton *pause = new QPushButton();
    playPause = new QStackedWidget();
    playPause->setMaximumWidth(buttonWidth);
    playPause->addWidget(pause);
    playPause->addWidget(play);
    playPause->setCurrentIndex(0);
    bot->addWidget(playPause);

    //Connect the buttons
    connect(play,SIGNAL(clicked()),this,SLOT(toggleVideo()));
    connect(pause,SIGNAL(clicked()),this,SLOT(toggleVideo()));

    //Make the scroll and add it
    videoSlider = new QSlider(Qt::Horizontal,this);
    qDebug() << "Video duration: " << player->duration();
    videoSlider->setRange(0, player->duration());
    //connect(player,SIGNAL(positionChanged(qint64)),videoSlider,)
    videoSlider->setMinimumWidth(200);
    bot->addWidget(new QLabel("Test"));
    bot->addWidget(videoSlider);

    //Connect scroll to VideoPlayer
    connect(videoSlider, &QSlider::sliderMoved, this, &Player::seek);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::modifySlider);
    connect(player,&QMediaPlayer::positionChanged,this,&Player::updateSlider);
    connect(videoSlider,&QSlider::sliderPressed,player,&QMediaPlayer::pause);
    connect(videoSlider,&QSlider::sliderReleased,player,&QMediaPlayer::play);

//    bot->addWidget(play);
//    bot->addWidget(pause);
    top->addLayout(bot);
    top->addStretch(1);

    // showtime!
    show();
}

void Player::playVideo(){
    //working on it
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
