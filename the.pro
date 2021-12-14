QT += core gui widgets multimedia multimediawidgets network

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    libraryPage/videolibrary.cpp \
    mainPage/menulayout.cpp \
        mainPage/navigation_button.cpp \
        mainPage/title_label.cpp \
        main_window.cpp \
        album_page.cpp \
        favourite_page.cpp \
        filter_page.cpp \
        library_page.cpp \
        map_page.cpp \
        player.cpp \
        settingspage.cpp \
        thumbnail_button.cpp \
        tomeo.cpp \
        video_player.cpp \
        # Map Files
        Map/image.cpp \
        Map/results.cpp \

HEADERS += \
    Map/image.h \
    libraryPage/videolibrary.h \
    mainPage/menulayout.h \
    mainPage/navigation_button.h \
    mainPage/title_label.h \
    main_window.h \
    album_page.h \
    favourite_page.h \
    filter_page.h \
    library_page.h \
    map_page.h \
    player.h \
    settingspage.h \
    thumbnail_button.h \
    video_file.h \
    video_player.h \
    # Map Files
    Map/image.h \
    Map/results.h \

RESOURCES += \
    resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS +=
