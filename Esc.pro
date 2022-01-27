QT -= gui
QT += bluetooth

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller_full_bridge.cpp \
        controller_half_bridge.cpp \
        esc.cpp \
        gattserver.cpp \
        i2cdev.cpp \
        main.cpp \
        message.cpp \
        sinarray.cpp

HEADERS += \
    constants.h \
    controller_full_bridge.h \
    controller_half_bridge.h \
    esc.h \
    gattserver.h \
    i2cdev.h \
    message.h \
    sinarray.h


QMAKE_INCDIR += /usr/local/include
QMAKE_LIBDIR += /usr/lib
QMAKE_LIBDIR += /usr/local/lib
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu
INCLUDEPATH += /usr/local/include

LIBS +=  -lwiringPi -li2c

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#sudo apt-get install libi2c-dev
#sudo apt-get install libwiringpi-dev
