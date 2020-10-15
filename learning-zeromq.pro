QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        publisherzmq.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:!macx: LIBS += -L$$PWD/lib/zeromq/lib/ -lzmq

INCLUDEPATH += $$PWD/lib/zeromq/inc
DEPENDPATH += $$PWD/lib/zeromq/inc

unix:!macx: PRE_TARGETDEPS += $$PWD/lib/zeromq/lib/libzmq.a

HEADERS += \
    publisherzmq.h
