#include "library_page.h"
#include <QVideoWidget>
#include "player.h"
#include <QGridLayout>
#include "libraryPage/videolibrary.h"
#include <QSize>

LibraryPage::LibraryPage(std::vector<VideoFile> &videos,Player *player) : QWidget() {


//        QVideoWidget *videoWidget = new QVideoWidget();
//        videoWidget->setStyleSheet("background: #FF00FF;");

//        Player *player = new Player;
//        player->setVideoOutput(videoWidget);

        VideoLibrary *library = new VideoLibrary(videos,player);
        //player->setContent(library->getButtons(), &videos);


        QGridLayout *libraryLayout = new QGridLayout();
        libraryLayout->setRowStretch(0, 1);
        libraryLayout->setRowStretch(1, 1);
        libraryLayout->addWidget(library, 0, 0);
        setLayout(libraryLayout);

}
