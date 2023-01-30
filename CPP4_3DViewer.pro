QT       += core gui svg openglwidgets opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QtGifImage/qtgifimage.pri)

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/Controller/Controller.cpp \
    Controller/Facade/Facade.cpp \
    Models/Affine/Affine.cpp \
    Models/Drawer/Drawer.cpp \
    Models/ModelReader/ModelReader.cpp \
    Models/SettingsParser/SettingsParser.cpp \
    View/MainWindow/View.cpp \
    View/Settings/Settings.cpp \
    main.cpp

HEADERS += \
    Controller/Controller/Controller.h \
    Controller/Facade/Facade.h \
    Models/Affine/Affine.h \
    Models/Drawer/Drawer.h \
    Models/ModelReader/ModelReader.h \
    Models/SettingsParser/SettingsParser.h \
    View/MainWindow/View.h \
    View/Settings/Settings.h

FORMS += \
    View/MainWindow/View.ui \
    View/Settings/Settings.ui


SUBDIRS += \
    QtGifImage/gifimage.pro

DEFINES += SETTINGSNAME=\\\"$(HOME)/Desktop/3DViewerSettings.txt\\\"

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icons.qrc
