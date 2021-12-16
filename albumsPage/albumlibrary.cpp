#include "albumlibrary.h"
#include <QPushButton>

static unsigned int hardAlbumsNr = 3;

AlbumLibrary::AlbumLibrary(std::vector<VideoFile> &vids, Player* player): videos(vids),player(player){
    setWidgetResizable(1);
    setAlbums();
}

void AlbumLibrary::setAlbums(){
    delete buttonScrollArea;
    buttons.clear();

    buttonScrollArea = new QWidget();
    buttonScrollArea->setProperty("type", "content");

    QGridLayout *layout = new QGridLayout();
    layout->setColumnStretch(0, 1);
    layout->setColumnStretch(1, 1);
    QSizePolicy buttonScrollAreaSizePolicy =  QSizePolicy();
    buttonScrollAreaSizePolicy.setHorizontalPolicy(QSizePolicy::Ignored);
    layout->setMargin(0);
    layout->setSpacing(0);
    buttonScrollArea->setLayout(layout);

    unsigned int i = 0;
    for (i = 0; i < hardAlbumsNr; i++) {
        AlbumButton *button = new AlbumButton(buttonScrollArea);
        //button->connect(button, SIGNAL(changeAlbum(int)), player, SLOT(playVideo(VideoFile*)));
        buttons.push_back(button);
        layout->addWidget(button, i / 2, i % 2);
    }

    QPushButton* add = new QPushButton();
    add->setText("New Album");
    layout->addWidget(add,i/2,i%2);


    setWidget(buttonScrollArea);
    buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);
}
