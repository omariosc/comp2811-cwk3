#include "libraryPage/videolibrary.h"
#include <QGridLayout>

#include <QPushButton>

VideoLibrary::VideoLibrary(std::vector<VideoFile> &vids, Player &player) : QScrollArea()
{
    setWidgetResizable(1);
    videos = vids;

    QWidget *buttonScrollArea = new QWidget();

    QGridLayout *layout = new QGridLayout();
    QSizePolicy buttonScrollAreaSizePolicy =  QSizePolicy();
    buttonScrollAreaSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
    buttonScrollArea->setLayout(layout);


    for (int i = 0; i < videos.size(); i++) {
        ThumbnailButton *button = new ThumbnailButton(buttonScrollArea);
        button->connect(button, SIGNAL(jumpTo(VideoFile*)), &player, SLOT(jumpTo(VideoFile*)));
        buttons.push_back(button);
        layout->addWidget(button, i / 4, i % 4);
        button->init(&videos.at(i));
    }


    setWidget(buttonScrollArea);
    buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);

}

//VideoLibrary::VideoLibrary() : QScrollArea(){
//    setWidgetResizable(1);
//    QWidget *buttonScrollArea = new QWidget();
//    QGridLayout *layout = new QGridLayout();
//    for (int i = 0; i < 10; i++) {
//        QPushButton *button = new QPushButton(buttonScrollArea);
//        layout->addWidget(button, i / 4, i % 4);
//    }
//    setWidget(buttonScrollArea);
//}


std::vector<ThumbnailButton*>* VideoLibrary::getButtons(){
    return &(buttons);
}
