#-------------------------------------------------
#
# Project created by QtCreator 2018-02-26T13:35:47
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PLFDirectory
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    addmemberform.cpp \
    logindialog.cpp \
    usersdialog.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    addmemberform.h \
    logindialog.h \
    usersdialog.h \
    user.h

FORMS    += mainwindow.ui \
    addmemberform.ui    \
    logindialog.ui \
    usersdialog.ui
