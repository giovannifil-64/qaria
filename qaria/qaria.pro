QT += core gui
QT += widgets

greaterThan(QT_MAJOR_VERSION, 6): QT += widgets

CONFIG += c++17

SOURCES += \
    model/aelist.cpp \
    model/atmosphericevent.cpp \
    model/atmosphericeventmodel.cpp \
    main.cpp \
    mainwindow.cpp \
    model/csvdata.cpp \
    model/csvfile.cpp \
    model/datamodel.cpp \
    view/datadelegate.cpp \
    view/dataview.cpp

HEADERS += \
    model/aelist.h \
    model/atmosphericevent.h \
    model/atmosphericeventmodel.h \
    mainwindow.h \
    model/csvdata.h \
    model/csvfile.h \
    model/datamodel.h \
    view/datadelegate.h \
    view/dataview.h

RESOURCES += \
    resources/resources.qrc

APP_NAME = QARIA

macx:ICON = $${PWD}/resources/macos_icon.icns

TEMPLATE = app

INCLUDEPATH += .

TARGET = qaria

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
