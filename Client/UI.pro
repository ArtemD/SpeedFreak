# -------------------------------------------------
# Project created by QtCreator 2010-02-23T14:17:30
# @author     Speed Freak team
# @copyright  (c) 2010 Speed Freak team
# @license    http://opensource.org/licenses/gpl-license.php GNU Public License
# -------------------------------------------------
QT += network \
    dbus \
    xml
TARGET = UI
TEMPLATE = app
SOURCES += main.cpp \
    carmainwindow.cpp \
    resultdialog.cpp \
    stringlistmodel.cpp \
    measuredialog.cpp \
    calculate.cpp \
    accelerometer.cpp \
    loginwindow.cpp \
    registration.cpp \
    measures.cpp \
    xmlwriter.cpp \
    xmlreader.cpp \
    httpclient.cpp \
    categorylist.cpp \
    welcomedialog.cpp \
    gpsdata.cpp \
    maemo5locationprivate.cpp \
    maemo5location.cpp \
    routedialog.cpp
HEADERS += carmainwindow.h \
    resultdialog.h \
    stringlistmodel.h \
    measuredialog.h \
    accelerometer.h \
    calculate.h \
    loginwindow.h \
    registration.h \
    measures.h \
    xmlwriter.h \
    xmlreader.h \
    httpclient.h \
    categorylist.h \
    welcomedialog.h \
    gpsdata.h \
    maemo5locationprivate.h \
    maemo5location.h \
    routedialog.h
FORMS += carmainwindow.ui \
    resultdialog.ui \
    measuredialog.ui \
    loginwindow.ui \
    registration.ui \
    welcomedialog.ui \
    routedialog.ui

contains(QT_CONFIG, hildon):CONFIG += hildon
CONFIG += link_pkgconfig

# Enable this to disable debugging
# DEFINES += QT_NO_DEBUG_OUTPUT
target.path += /usr/lib
devincludes.files = $$HEADERS
devincludes.path += /usr/include/$$TEMPLATE$$TARGET
INSTALLS += target \
    devincludes
PKGCONFIG += glib-2.0 \
    liblocation
exists(/usr/lib/liblocation.so) {
    DEFINES += LIBLOCATION
    message(liblocation found)
}
