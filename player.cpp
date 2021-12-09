#include "player.h"
#include "QLabel"

//static const int buttonWidth = 30;
static const int butMaxWidth = 50;

Player::Player(std::vector<VideoFile> videos,QStackedWidget* toggler): toggler(toggler)
{
    this->setMinimumSize(320,320);

    QVideoWidget *videoWidget = new QVideoWidget();
    videoWidget->setMinimumSize(300,300);

    // the QMediaPlayer which controls the playback
    player = new VideoPlayer();
    player->setVideoOutput(videoWidget);

    // tell the player what buttons and videos are available
    currentVideo = &videos[0];
    player->setContent(currentVideo);
    //player->setContent(NULL);

    // create the main window and layout
    QVBoxLayout *top = new QVBoxLayout();
    setLayout(top);
    setWindowTitle("Video Player");

    // add the video and the buttons
    top->addWidget(videoWidget);


    //Create the button layout
    QHBoxLayout *bot = new QHBoxLayout();

    //Create and add the back button
    QPushButton *back = new QPushButton();
    back->setText("Back");
    back->setMaximumWidth(butMaxWidth);
    bot->addWidget(back);

    //Connect it to QStackedWidget
    connect(back,&QPushButton::clicked,this,&Player::quitPlayer);


    //Create the play/pause stacked widget
    QPushButton *play = new QPushButton();
    QPushButton *pause = new QPushButton();
    play->setText("&Play");
    pause->setText("&Pause");
    playPause = new QStackedWidget();
    playPause->setMaximumWidth(butMaxWidth);
    playPause->addWidget(pause);
    playPause->addWidget(play);
    playPause->setCurrentIndex(1);
    bot->addWidget(playPause);

    //Connect the play/pause buttons
    connect(play,SIGNAL(clicked()),this,SLOT(toggleVideo()));
    connect(pause,SIGNAL(clicked()),this,SLOT(toggleVideo()));

    //Create the "favorite" button
    QPushButton *favorite = new QPushButton();
    favorite->setText("Fav");
    favorite->setMaximumWidth(butMaxWidth);
    bot->addWidget(favorite);

    //And connect it
    connect(favorite,&QPushButton::clicked,this,&Player::toggleFavorite);

    //Make the scroll and add it
    videoSlider = new QSlider(Qt::Horizontal,this);
    qDebug() << "Video duration: " << player->duration();
    videoSlider->setRange(0, player->duration());
    videoSlider->setMinimumWidth(200);

    bot->addWidget(new QLabel("Seeker:"));
    bot->addWidget(videoSlider);

    //Connect scroll to VideoPlayer
    connect(videoSlider, &QSlider::sliderMoved, this, &Player::seek);
    connect(player,&QMediaPlayer::durationChanged,this,&Player::modifySlider);
    connect(player,&QMediaPlayer::positionChanged,this,&Player::updateSlider);
    connect(videoSlider,&QSlider::sliderPressed,player,&QMediaPlayer::pause);
    connect(videoSlider,&QSlider::sliderReleased,player,&QMediaPlayer::play);

    top->addLayout(bot);
    top->addStretch(1);
    player->pause();
    // showtime!
    show();
}

void Player::playVideo(VideoFile* newVideo){
    player->stop();
    if(toggler->currentIndex() != 1) toggler->setCurrentIndex(1);
    playPause->setCurrentIndex(1);
    player->setContent(newVideo);
    currentVideo = newVideo;
    player->pause();
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
