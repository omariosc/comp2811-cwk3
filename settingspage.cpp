#include "settingspage.h"
#include <QVBoxLayout>
#include <QLabel>
#include "mainPage/title_label.h"
#include "mainPage/navigation_button.h"
#include <QVariant>

SettingsPage::SettingsPage(QWidget *parent) : QDialog(parent) {
    //setStyleSheet("background: #000000;");
    setModal(1);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    if (parent) {
        resize(parent->width()-40, parent->height()-500);
    }


    TitleLabel* title = new TitleLabel();
    title->setText("Settings");

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



    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(header);
    layout->addStretch();
    setLayout(layout);
    show();
}

void SettingsPage::returnBack(){
    close();
}

