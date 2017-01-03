#-------------------------------------------------
#
# Project created by QtCreator 2016-12-14T15:38:24
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET =  CuteVCF
TEMPLATE = app

CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT

# On linux, compile htslib
unix {
mytarget.target = $$PWD/htslib/libhts.so
mytarget.commands = cd $$PWD/htslib; make -j4
mytarget_clean.commands = cd $$PWD/htslib; make clean
QMAKE_EXTRA_TARGETS += mytarget
PRE_TARGETDEPS += $$PWD/htslib/libhts.so
INCLUDEPATH+=$$PWD/htslib
LIBS += -L$$PWD/htslib -lhts


}

# On windows use libhts.a made from msys2.
win32{
LIBS += -L$$PWD/win32 -lhts

INCLUDEPATH += $$PWD/htslib
DEPENDPATH += $$PWD/htslib
}


include("QFontIcon/QFontIcon.pri")





RESOURCES += files.qrc

HEADERS += \
    aboutdialog.h \
    createindexdialog.h \
    infowidget.h \
    mainwindow.h \
    qtabix.h \
    samplewidget.h \
    vcfheader.h \
    vcfline.h \
    vcfmodel.h

SOURCES += \
    aboutdialog.cpp \
    createindexdialog.cpp \
    infowidget.cpp \
    mainwindow.cpp \
    main.cpp \
    qtabix.cpp \
    samplewidget.cpp \
    vcfheader.cpp \
    vcfline.cpp \
    vcfmodel.cpp
