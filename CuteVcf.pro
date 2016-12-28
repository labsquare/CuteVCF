#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T15:38:24
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# On linux, compile htslib
unix {
mytarget.target = $$PWD/htslib/libhts.so
mytarget.commands = cd $$PWD/htslib; make -j4
mytarget_clean.commands = cd $$PWD/htslib; make clean
QMAKE_EXTRA_TARGETS += mytarget
PRE_TARGETDEPS += $$PWD/htslib/libhts.so
INCLUDEPATH+=$$PWD/htslib
LIBS += -L$$PWD/htslib -lhts

TARGET =  CuteVcf
TEMPLATE = app
}

# On windows use libhts.a made from msys2.
win32{
LIBS += -L$$PWD/win32 -lhts

INCLUDEPATH += $$PWD/htslib
DEPENDPATH += $$PWD/htslib
}





SOURCES += main.cpp\
        mainwindow.cpp \
    qtabix.cpp \
    vcfmodel.cpp \
    vcfline.cpp \
    infowidget.cpp \
    samplewidget.cpp \
    vcfheader.cpp \
    aboutdialog.cpp \
    createindexdialog.cpp

HEADERS  += mainwindow.h \
    qtabix.h \
    vcfmodel.h \
    vcfline.h \
    infowidget.h \
    samplewidget.h \
    vcfheader.h \
    aboutdialog.h \
    createindexdialog.h

RESOURCES += \
    icons/icons.qrc

DISTFILES += \
    icons/squares.gif


