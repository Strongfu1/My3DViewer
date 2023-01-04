QT       += core gui svg openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    affine.cpp \
    controller.cpp \
    drawer.cpp \
    facade.cpp \
    ModelReader.cpp \
    main.cpp \
    parsSavedSettings.cpp \
    settings.cpp \
    view.cpp

HEADERS += \
    affine.h \
    controller.h \
    drawer.h \
    facade.h \
    ModelReader.h \
    parsSavedSettings.h \
    settings.h \
    view.h

FORMS += \
    settings.ui \
    view.ui


SUBDIRS += \
    QtGifImage/gifimage.pro

DEFINES += SETTINGSNAME=\\\"$(HOME)/Desktop/3DViewerSettings.txt\\\"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
