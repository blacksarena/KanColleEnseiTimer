#-------------------------------------------------
#
# Project created by QtCreator 2018-05-19T20:11:41
#
#-------------------------------------------------

QT       += core gui widgets
QMAKE_CXXFLAGS += -std=c++0x

TARGET = KanColleEnseiTimer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ensei_data.cpp \
    count_down_timer.cpp \
    ensei_settings.cpp \
    screen_shot.cpp \
    countdown_from_the_middle.cpp

HEADERS  += mainwindow.h \
    ensei_data.h \
    count_down_timer.h \
    ensei_settings.h \
    screen_shot.h \
    countdown_from_the_middle.h

FORMS    += mainwindow.ui \
    countdown_from_the_middle.ui

CONFIG(debug, release|debug):DEFINES += _DEBUG

DISTFILES += \
    algorithm.txt \
    readme.md

RESOURCES += \
    resource.qrc

LIBS += -lpcap
