QT       += core gui network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    chatclient.cpp \
    chatserverform.cpp \
    clientlogthread.cpp \
    clientmanagerform.cpp \
    logthread.cpp \
    main.cpp \
    mainwindow.cpp \
    ordermanagerform.cpp \
    productmanagerform.cpp

HEADERS += \
    chatclient.h \
    chatserverform.h \
    clientlogthread.h \
    clientmanagerform.h \
    logthread.h \
    mainwindow.h \
    ordermanagerform.h \
    productmanagerform.h

FORMS += \
    chatclient.ui \
    chatserverform.ui \
    clientmanagerform.ui \
    mainwindow.ui \
    ordermanagerform.ui \
    productmanagerform.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icon.qrc

DISTFILES +=
