#include "settingspage.h"
#include <QVBoxLayout>
#include <QLabel>
#include "mainPage/title_label.h"
#include "mainPage/navigation_button.h"
#include "mainPage/menulayout.h"
#include <QComboBox>
#include <QVariant>
#include <QLineEdit>

SettingsPage::SettingsPage(QStackedWidget *parent) : QWidget() {

    stackedParent = parent;

    TitleLabel* title = new TitleLabel();
    title->setText("SETTINGS");

    NavigationButton *returnButton = new NavigationButton("BACK");
    returnButton->setIcon(QIcon(":/goback-white-icon"));
    connect(returnButton, &NavigationButton::clicked, this, &SettingsPage::returnBack);

    MenuLayout *headerLayout = new MenuLayout();
    headerLayout->addWidget(title, 0, 1, 1, 2);
    headerLayout->addWidget(returnButton, 0, 3);

    QWidget * header = new QWidget();
    header->setProperty("type", "menuBackground");
    header->setLayout(headerLayout);

    QGridLayout* settingsLayout = new QGridLayout();
    settingsLayout->setMargin(10);
    settingsLayout->setSpacing(0);

    QLabel *textColor = new QLabel("Text Colour: ");
    textColor->setProperty("type", "setting");
    textColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QComboBox *textColorCB = new QComboBox();
    QStringList textColors = {"White", "Black", "Red", "Green", "Blue"};
    textColorCB->insertItems(0, textColors);
    textColorCB->setInsertPolicy(QComboBox::InsertAlphabetically);
    settingsLayout->addWidget(textColor, 0, 0);
    settingsLayout->addWidget(textColorCB, 0, 1);

    QLabel *backgroundColor = new QLabel("Background: ");
    backgroundColor->setProperty("type", "setting");
    backgroundColor->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QComboBox *backgroundColorCB = new QComboBox();
    QStringList backgroundColors = {"White", "Red", "Green", "Blue"};
    backgroundColorCB->insertItems(0, backgroundColors);
    backgroundColorCB->setInsertPolicy(QComboBox::InsertAlphabetically);
    settingsLayout->addWidget(backgroundColor, 1, 0);
    settingsLayout->addWidget(backgroundColorCB, 1, 1);
    backgroundColorCB->setItemText(0, "Black");

    QLabel *language = new QLabel("Language: ");
    language->setProperty("type", "setting");
    language->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    QComboBox *languageCB = new QComboBox();
    QStringList languages = {"English", "Romanian"};
    languageCB->insertItems(0, languages);
    languageCB->setInsertPolicy(QComboBox::InsertAlphabetically);
    settingsLayout->addWidget(language, 2, 0);
    settingsLayout->addWidget(languageCB, 2, 1);

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
}

void SettingsPage::returnBack(){
    stackedParent->setCurrentIndex(0);
}
