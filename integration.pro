QT       += core network
QT       += core gui network
QT       += core gui printsupport

#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql multimedia
QT += serialport
QT += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Atelier_Connexion
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    DuMessengerConnectionDialog.cpp \
    DuMessengerServer.cpp \
    DuMessengerSocket.cpp \
    QRCodeGenerator.cpp \
    arduino.cpp \
    avion.cpp \
    bagageee.cpp \
    billet.cpp \
    calculatrice.cpp \
    dialog_stats.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    qcustomplot.cpp \
    smtp.cpp \
    vols.cpp \
    widget.cpp

HEADERS += \
    DuMessengerConnectionDialog.h \
    DuMessengerServer.h \
    DuMessengerSocket.h \
    QRCodeGenerator.h \
    arduino.h \
    avion.h \
    bagageee.h \
    billet.h \
    calculatrice.h \
    dialog_stats.h \
        mainwindow.h \
    connection.h \
    qcustomplot.h \
    smtp.h \
    vols.h \
    widget.h

FORMS += \
        DuMessengerConnectionDialog.ui \
        calculatrice.ui \
        dialog_stats.ui \
        mainwindow.ui \
        widget.ui

QMAKE_CXXFLAGS  += -std=gnu++11

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
