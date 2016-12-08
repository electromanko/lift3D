#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T21:44:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lift3D
TEMPLATE = app


SOURCES += src/main.cpp\
           src/mainwindow.cpp\
           src/glwidget.cpp\
           src/geometryengine.cpp \
            src/paramwidget.cpp \
            src/geometry_kernel.cpp \
            src/geometry_element.cpp \
            src/geometry_unit.cpp

HEADERS  += include/mainwindow.h\
            include/glwidget.h\
            include/geometryengine.h \
            include/paramwidget.h \
            include/geometry_kernel.h \
            include/geometry_element.h \
            include/geometry_unit.h

FORMS    += form/mainwindow.ui

RESOURCES += \
    res/shaders.qrc \
    res/textures.qrc
    res/cube.png

DISTFILES +=

