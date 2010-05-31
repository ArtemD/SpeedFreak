# -------------------------------------------------
# Project created by QtCreator 2010-03-29T09:21:42
# @author     Speed Freak team
# @copyright  (c) 2010 Speed Freak team
# @license    http://opensource.org/licenses/gpl-license.php GNU Public License
# -------------------------------------------------
QT += dbus \
    network \
    xml
TARGET = speedfreak
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp \
    creditsdialog.cpp \
    routedialog.cpp \
    routesavedialog.cpp \
    welcomedialog.cpp \
    usersettings.cpp \
    resultdialog.cpp \
    instructionsdialog.cpp \
    settingsdialog.cpp \
    accelerationstart.cpp \
    accrealtimedialog.cpp \
    accelerometer.cpp \
    movingaverage.cpp \
    calculate.cpp \
    calibratedialog.cpp \
    topresultdialog.cpp \
    categorylist.cpp \
    httpclient.cpp \
    xmlreader.cpp \
    xmlwriter.cpp \
    gpsdata.cpp \
    maemo5locationprivate.cpp \
    maemo5location.cpp \
    helpdialog.cpp \
    helpresultsdialog.cpp \
    helpaccelerationdialog.cpp \
    helproutingdialog.cpp \
    helpsettingsdialog.cpp \
    custombutton.cpp \
    profiledialog.cpp \
	filereader.cpp \
    usersdialog.cpp \
    registerdialog.cpp \
    helpusersdialog.cpp
HEADERS += mainwindow.h \
    creditsdialog.h \
    routedialog.h \
    routesavedialog.h \
    welcomedialog.h \
    usersettings.h \
    resultdialog.h \
    instructionsdialog.h \
    settingsdialog.h \
    accelerationstart.h \
    accrealtimedialog.h \
    accelerometer.h \
    movingaverage.h \
    calculate.h \
    calibratedialog.h \
    topresultdialog.h \
    categorylist.h \
    httpclient.h \
    xmlreader.h \
    xmlwriter.h \
    maemo5locationprivate.h \
    maemo5location.h \
    gpsdata.h \
    helpdialog.h \
    helpresultsdialog.h \
    helpaccelerationdialog.h \
    helproutingdialog.h \
    helpsettingsdialog.h \
    custombutton.h \
    profiledialog.h \
	filereader.h \
    usersdialog.h \
    registerdialog.h \
    helpusersdialog.h
FORMS += mainwindow.ui \
    creditsdialog.ui \
    routedialog.ui \
    routesavedialog.ui \
    welcomedialog.ui \
    resultdialog.ui \
    instructionsdialog.ui \
    settingsdialog.ui \
    accelerationstartdialog.ui \
    accrealtimedialog.ui \
    calibratedialog.ui \
    topresultdialog.ui \
    helpdialog.ui \
    helpresultsdialog.ui \
    helpaccelerationdialog.ui \
    helproutingdialog.ui \
    helpsettingsdialog.ui \
    profiledialog.ui \
    usersdialog.ui \
    registerdialog.ui \
    helpusersdialog.ui
RESOURCES += graphics.qrc
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
