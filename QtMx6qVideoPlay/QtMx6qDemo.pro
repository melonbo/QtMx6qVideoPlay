TEMPLATE = app
TARGET = QtMx6qDemo
QMAKESPEC = /usr/local/Trolltech/QtEmbedded-4.6.0-arm/mkspecs/qws/linux-arm-g++/
QMAKEDIR = /usr/local/Trolltech/QtEmbedded-4.6.0-arm/
ROOTFSDIR = /usr/local/Trolltech/QtEmbedded-4.6.0-arm/
QMAKE_INCDIR = $$ROOTFSDIR/usr/include \
    $$ROOTFSDIR/usr/include/glib-2.0 \
    $$ROOTFSDIR/usr/lib/glib-2.0/include/ \
    $$ROOTFSDIR/usr/include/gstreamer-0.10/ \
    $$ROOTFSDIR/usr/include/libxml2/ \
    $$ROOTFSDIR/usr/include/freetype2 \
    $$ROOTFSDIR/usr/include/imx-mm/vpu \
    $$ROOTFSDIR/usr/src/linux/include \
    $$QMAKEDIR/include/phonon \
    $$QMAKEDIR/include/Qt \
    $$QMAKEDIR/include/Qt3Support \
    $$QMAKEDIR/include/QtCore \
    $$QMAKEDIR/include/QtGui \
    $$QMAKEDIR/include/QtMultimedia \
    $$QMAKEDIR/include/QtNetwork \
    $$QMAKEDIR/include/QtScript \
    $$QMAKEDIR/include/QtScriptTools \
    $$QMAKEDIR/include/QtSql \
    $$QMAKEDIR/include/QtSvg \
    $$QMAKEDIR/include/QtTest \
    $$QMAKEDIR/include/QtXml \
    $$QMAKEDIR/include/QtXmlPatterns \
    $$QMAKEDIR/include/

INCLUDEPATH += /usr/local/lib/lib_a9/include/

QMAKE_LIBDIR = $$ROOTFSDIR/usr/lib \
    $$QMAKEDIR/lib
QMAKE_MOC = $$QMAKEDIR/bin/moc
QMAKE_UIC = $$QMAKEDIR/bin/uic
QT += core \
    gui
HEADERS +=    qtmx6qdemo.h CDecThread.h
SOURCES +=  main.cpp \
   decode_stream.cpp \
   CDecThread.cpp \
   bmp_utils.cpp \
   yuv2rgb.cpp \
    qtmx6qdemo.cpp
FORMS += qtmx6qdemo.ui 

RESOURCES += 
LIBS += -L./ \
    -L /usr/local/lib/lib_a9/ \
     -lfslvpuwrap \ 
     -lvpu \
     -lipu 
QMAKE_PRE_LINK =
QMAKE_POST_LINK = cp -f QtMx6qDemo /opt/nfsroot
CONFIG += debug
