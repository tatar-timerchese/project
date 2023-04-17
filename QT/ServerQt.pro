QT -= gui
QT += network
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    mytcpserver.cpp

HEADERS += \
    db.h \
    functions.h \
    mytcpserver.h

FORMS += \
    mytcpserver.ui

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
