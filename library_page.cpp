#include "library_page.h"
#include <QVideoWidget>
#include "player.h"
#include <QGridLayout>
#include <QVBoxLayout>

LibraryPage::LibraryPage(std::vector<VideoFile> &videos) : QWidget() {


        QVideoWidget *videoWidget = new QVideoWidget();
        Player *player = new Player;
        player->setVideoOutput(videoWidget);

        QWidget *buttonWidget = new QWidget();

        std::vector<ThumbnailButton*> buttons;

        QGridLayout *layout = new QGridLayout();
        buttonWidget->setLayout(layout);

        for (int i = 0; i < videos.size(); i++) {
            ThumbnailButton *button = new ThumbnailButton(buttonWidget);
            button->connect(button, SIGNAL(jumpTo(VideoFile*)), player, SLOT(jumpTo(VideoFile*))); // when clicked, tell the player to play.
            buttons.push_back(button);
            layout->addWidget(button, i / 3, i % 3);
            button->init(&videos.at(i));
        }
        // tell the player what buttons and videos are available
        player->setContent(&buttons, &videos);

        QVBoxLayout *libraryLayout = new QVBoxLayout();
        libraryLayout->addWidget(videoWidget);
        libraryLayout->addWidget(buttonWidget);
        setLayout(libraryLayout);
}
