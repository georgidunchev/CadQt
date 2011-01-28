#-------------------------------------------------
#
# Project created by QtCreator 2010-12-06T16:47:56
#
#-------------------------------------------------

QT       += core gui

TARGET = CadQt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cadscene.cpp \
    caditem.cpp \
    cadlineitem.cpp \
    cadrectitem.cpp \
    cadpolyitem.cpp \
    cadboundingcircle.cpp \
    cadcontrolpointsitem.cpp \
    cadcontrolpointrectitem.cpp \
    cadcurveitem.cpp

HEADERS  += mainwindow.h \
    cadscene.h \
    caditem.h \
    cadlineitem.h \
    cadrectitem.h \
    cadpolyitem.h \
    cadboundingcircle.h \
    cadcontrolpointsitem.h \
    cadcontrolpointrectitem.h \
    cadcurveitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    CadResources.qrc

OTHER_FILES += \
    ToDo.txt
