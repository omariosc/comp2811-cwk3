#include "libraryPage/videolibrary.h"
#include <QGridLayout>
#include "player.h"

#include <QPushButton>

VideoLibrary::VideoLibrary(std::vector<VideoFile> &vids,Player* player) : QScrollArea(){
    setWidgetResizable(1);
    mediaPlayer = player;
    setVideos(vids);
}

void VideoLibrary::setVideos(std::vector<VideoFile> &vids){

    videos = vids;
    buttonScrollArea = new QWidget();
    buttonScrollArea->setProperty("type", "content");

    QGridLayout *layout = new QGridLayout();
    QSizePolicy buttonScrollAreaSizePolicy =  QSizePolicy();
    buttonScrollAreaSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
    layout->setMargin(0);
    layout->setSpacing(0);
    buttonScrollArea->setLayout(layout);


    for (int i = 0; i < videos.size(); i++) {
        ThumbnailButton *button = new ThumbnailButton(buttonScrollArea);
        button->connect(button, SIGNAL(jumpTo(VideoFile*)), mediaPlayer, SLOT(playVideo(VideoFile*)));
        buttons.push_back(button);
        layout->addWidget(button, i / 4, i % 4);
        button->init(&videos.at(i));
    }


    setWidget(buttonScrollArea);
    buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);
}


std::vector<ThumbnailButton*>* VideoLibrary::getButtons(){
    return &(buttons);
}

void VideoLibrary::changeVideos(std::vector<VideoFile> &vids) {
    delete buttonScrollArea;
    buttons.clear();
    videos.clear();

}
