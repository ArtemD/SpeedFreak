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
    categorylist.cpp
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
    categorylist.h
FORMS += carmainwindow.ui \
    resultdialog.ui \
    measuredialog.ui \
    loginwindow.ui \
    registration.ui
