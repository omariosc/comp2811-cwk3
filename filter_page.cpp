#include "filter_page.h"

#include "libraryPage/videolibrary.h"
#include <QGridLayout>
#include <QComboBox>
#include <QLabel>


FilterPage::FilterPage(std::vector<VideoFile> &videos, Player *player) : QWidget() {

//    QLabel *textColor = new QLabel("Text Colour: ");
//    textColor->setProperty("type", "setting");
//    textColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
//    QComboBox *textColorCB = new QComboBox();
//    QStringList textColors = {"White", "Black", "Red", "Green", "Blue"};
//    textColorCB->insertItems(0, textColors);
//    textColorCB->setInsertPolicy(QComboBox::InsertAlphabetically);
//    settingsLayout->addWidget(textColor, 0, 0);
//    settingsLayout->addWidget(textColorCB, 0, 1);

    VideoLibrary *library = new VideoLibrary(videos,player);

    QGridLayout *libraryLayout = new QGridLayout();
    libraryLayout->addWidget(library, 0, 0);
    setLayout(libraryLayout);
}
