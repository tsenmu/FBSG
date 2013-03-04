#-------------------------------------------------
#
# Project created by QtCreator 2013-01-24T16:28:10
#
#-------------------------------------------------

QT       += core gui

TARGET = FactoryBusinessSimulatorGUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    startwidget.cpp \
    confwidget.cpp \
    mainwidget.cpp \
    menuwidget.cpp \
    coordinator.cpp \
    config.cpp \
    listwidget.cpp \
    decisionwidget.cpp \
    marketingwidget.cpp \
    colorstatus.cpp \
    endwidget.cpp \
    flowlayout.cpp \
    playermanager.cpp \
    marketsdialog.cpp

HEADERS  += mainwindow.h \
    startwidget.h \
    confwidget.h \
    mainwidget.h \
    menuwidget.h \
    coordinator.h \
    config.h \
    listwidget.h \
    decisionwidget.h \
    marketingwidget.h \
    colorstatus.h \
    endwidget.h \
    flowlayout.h \
    playermanager.h \
    player.h \
    marketsdialog.h

FORMS    += mainwindow.ui \
    startwidget.ui \
    confwidget.ui \
    mainwidget.ui \
    menuwidget.ui \
    listwidget.ui \
    decisionwidget.ui \
    colorstatus.ui \
    endwidget.ui \
    marketsdialog.ui

RESOURCES += \
    image.qrc
