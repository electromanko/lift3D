#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T21:44:57
#
#-------------------------------------------------

win32:RC_ICONS += res/icon/WinchLogo.ico

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lift3D
TEMPLATE = app

SOURCES += src/main.cpp\
           src/mainwindow.cpp\
           src/glwidget.cpp\
           src/geometryengine.cpp \
            src/geometry_kernel.cpp \
            src/geometry_element.cpp \
            src/geometry_unit.cpp \
    src/gnetraw.cpp \
    src/lifter.cpp \
    src/lift.cpp \
    src/lifttable.cpp \
    src/cmddialog.cpp \
    src/lifter3d.cpp \
    src/joywidget.cpp \
    src/controlwidget.cpp \
    src/liftconfig.cpp \
    src/iowidget.cpp \
    src/iomqtt.cpp \
    src/settingsdialog.cpp \
    src/gdatagram.cpp

HEADERS  += include/mainwindow.h\
            include/glwidget.h\
            include/geometryengine.h \
            include/geometry_kernel.h \
            include/geometry_element.h \
            include/geometry_unit.h \
            include/gnetraw.h \
            include/lifter.h \
            include/lift.h \
            include/lifttable.h \
    include/cmddialog.h \
    include/lifter3d.h \
    include/joywidget.h \
    include/controlwidget.h \
    include/liftconfig.h \
    include/iowidget.h \
    include/iomqtt.h \
    include/settingsdialog.h \
    include/gdatagram.h

TRANSLATIONS += translations/lift3D_ru.ts
#TRANSLATIONS += translations/lift3D_en.ts

FORMS    += form/mainwindow.ui

RESOURCES += \
    res/shaders.qrc \
    res/textures.qrc \
    res/config.qrc \
    res/icon.qrc

DISTFILES += \
    config.gc

#QMAKE_LFLAGS = -static -static-libgcc -static-libstdc++  -Wl,-enable-auto-import -Wl,-enable-runtime-pseudo-reloc


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../qmqtt/build-qmqtt-Desktop_Qt_5_6_2_MinGW_32bit-Debug/lib/ -lqmqtt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../qmqtt/build-qmqtt-Desktop_Qt_5_6_2_MinGW_32bit-Debug/lib/ -lqmqttd
else:unix: LIBS += -L$$PWD/../../qmqtt/build-qmqtt-Desktop_Qt_5_6_2_MinGW_32bit-Debug/lib/ -lqmqtt

INCLUDEPATH += $$PWD/../../qmqtt/qmqtt-master/src/mqtt
DEPENDPATH += $$PWD/../../qmqtt/qmqtt-master/src/mqtt
