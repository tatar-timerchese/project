QT += testlib
QT -= gui
QT+= core
QT += sql 
QT += network 

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
CONFIG += c++17 console

TEMPLATE = app

SOURCES +=  \
    ./../../../functions.cpp \
    ./../../../mytcpserver.cpp
    ./task4.cpp \

HEADERS += \
    ./../../../db.h \
    ./../../../functions.h \
    ./../../../mytcpserver.h

DEFINES += QT_DEPRECATED_WARNINGS

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
