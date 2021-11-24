//
// Created by twak on 11/11/2019.
//


#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H
#include <QPushButton>
#include <QUrl>
#include "videoFile.h"


class TheButton : public QPushButton {
    Q_OBJECT

public:
    VideoFile* info;

     TheButton(QWidget *parent) :  QPushButton(parent) {
         setIconSize(QSize(200,110));
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
    }

    void init(VideoFile* i);

private slots:
    void clicked();

signals:
    void jumpTo(VideoFile*);

};

#endif //CW2_THE_BUTTON_H
