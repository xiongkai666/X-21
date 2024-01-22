QT       += core gui xml multimedia network widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    abstractrhxcontroller.cpp \
    boardidentifier.cpp \
    controllerinterface.cpp \
    controlwindow.cpp \
    main.cpp \
    rhxcontroller.cpp \
    startupdialog.cpp \
    statusbars.cpp

HEADERS += \
    PionwayDLL.h \
    abstractrhxcontroller.h \
    boardidentifier.h \
    controllerinterface.h \
    controlwindow.h \
    rhxcontroller.h \
    rhxglobals.h \
    startupdialog.h \
    statusbars.h \
    systemstate.h

TRANSLATIONS += \
    X-21_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/./ -lPionway

INCLUDEPATH += $$PWD/.
DEPENDPATH += $$PWD/.

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/./Pionway.lib

RESOURCES += \
    X-021.qrc

