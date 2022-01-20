QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        controller_half_bridge.cpp \
        controller_three_phase.cpp \
        esc.cpp \
        i2cdev.cpp \
        main.cpp \
        sinarray.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    constants.h \
    controller_half_bridge.h \
    controller_three_phase.h \
    esc.h \
    i2cdev.h \
    sinarray.h


QMAKE_INCDIR += /usr/local/include
QMAKE_LIBDIR += /usr/lib
QMAKE_LIBDIR += /usr/local/lib
QMAKE_LIBDIR += /usr/lib/x86_64-linux-gnu
INCLUDEPATH += /usr/local/include

LIBS +=  -lwiringPi -li2c

#sudo apt-get install libi2c-dev
#sudo apt-get install libwiringpi-dev
