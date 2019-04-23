QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG+=console c++14



INCLUDEPATH+="../../"
INCLUDEPATH+="googletest"
INCLUDEPATH+="googletest/include"
INCLUDEPATH+="googlemock"
INCLUDEPATH+="googlemock/include"

SOURCES += \
    main.cpp \
    googletest/src/gtest-all.cc \
    googlemock/src/gmock-all.cc \
    ../../form.cpp \
    ../../Game.cpp \
    ../../history.cpp \
    ../../mainwindow.cpp

FORMS += \
    ../../form.ui \
    ../../history.ui \
    ../../mainwindow.ui

HEADERS += \
    ../../form.h \
    ../../Game.h \
    ../../history.h \
    ../../mainwindow.h


