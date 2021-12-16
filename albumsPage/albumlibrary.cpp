#include "albumlibrary.h"
#include <QPushButton>
#include <string>

static unsigned int hardAlbumsNr = 3;

AlbumLibrary::AlbumLibrary(std::vector<VideoFile*> &vids, VideoLibrary* library, QStackedWidget* toggler): videos(vids), library(library), toggler(toggler){
    setWidgetResizable(1);
    buttonScrollArea = new QScrollArea();
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
        button->setAlbum(i+1);
        QString name = "ALBUM " + QString::number(i+1);
        button->setText(name);
        button->connect(button, SIGNAL(changeAlbum(int)), this, SLOT(filterForAlbum(int)));
        buttons.push_back(button);
        layout->addWidget(button, i / 2, i % 2);
    }

    QToolButton* add = new QToolButton();
    add->setProperty("type", "albumButton");
    add->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    add->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    add->setMinimumHeight(45);
    add->setText("New Album");
    add->setIcon(QIcon(":/addLibraryIcon"));
    add->setIconSize(QSize(50,60));
    layout->addWidget(add,i/2,i%2);


    setWidget(buttonScrollArea);
    buttonScrollArea->setSizePolicy(buttonScrollAreaSizePolicy);
}

void AlbumLibrary::switchToAlbum(){
    toggler->setCurrentIndex(1);
}

void AlbumLibrary::switchBack(){
    toggler->setCurrentIndex(0);
}

void AlbumLibrary::filterForAlbum(int album){
    std::vector<VideoFile*> currentVideos;
    for (VideoFile* video : videos) {
        if (video->album == album) {
            currentVideos.push_back(video);
        }
    }
    switchToAlbum();
    library->changeVideos(currentVideos);
}
