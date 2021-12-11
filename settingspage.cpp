#include "settingspage.h"
#include <QVBoxLayout>
#include <QLabel>
#include "mainPage/title_label.h"
#include "mainPage/navigation_button.h"
#include <QVariant>
#include <QLineEdit>

SettingsPage::SettingsPage(QWidget *parent) : QDialog(parent) {
    //setStyleSheet("background: #000000;");
    setModal(1);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    if (parent) {
        resize(parent->width(), parent->height());
    }


    TitleLabel* title = new TitleLabel();
    title->setText("SETTINGS");

    NavigationButton *returnButton = new NavigationButton("BACK");
    returnButton->setIcon(QIcon(":/returnIcon"));
    connect(returnButton, &NavigationButton::clicked, this, &SettingsPage::returnBack);



    QGridLayout *headerLayout = new QGridLayout();
    headerLayout->setColumnStretch(0, 1);
    headerLayout->setColumnStretch(1, 1);
    headerLayout->setColumnStretch(2, 1);
    headerLayout->setColumnStretch(3, 1);
    headerLayout->setMargin(0);
    headerLayout->setSpacing(0);
    headerLayout->addWidget(title, 0, 1, 1, 2);
    headerLayout->addWidget(returnButton, 0, 3);

    QWidget * header = new QWidget();
    header->setProperty("type", "menuBackground");
    header->setLayout(headerLayout);

    QLabel *textColor = new QLabel("Text Colour: ");
    textColor->setAlignment(Qt::AlignRight);
    QLineEdit * textColorLE = new QLineEdit();

    QLabel *backgroundColor = new QLabel("Background Colour: ");
    backgroundColor->setAlignment(Qt::AlignRight);
    QLineEdit * backgroundColorLE = new QLineEdit();

    QLabel *language = new QLabel("Language: ");
    language->setAlignment(Qt::AlignRight);
    QLineEdit * languageLE = new QLineEdit();

    QGridLayout* settingsLayout = new QGridLayout();
    settingsLayout->addWidget(textColor, 0,0);
    settingsLayout->addWidget(textColorLE, 0,1);
    settingsLayout->addWidget(backgroundColor, 1,0);
    settingsLayout->addWidget(backgroundColorLE, 1,1);
    settingsLayout->addWidget(language, 2,0);
    settingsLayout->addWidget(languageLE, 2,1);

    QWidget *settings = new QWidget();
    settings->setProperty("type", "content");
    settings->setLayout(settingsLayout);





    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(header);
    layout->addWidget(settings);
    layout->addStretch();
    setLayout(layout);
    show();
}

void SettingsPage::returnBack(){
    close();
}

