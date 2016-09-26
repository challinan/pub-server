#-------------------------------------------------
#
# Project created by QtCreator 2016-08-31T09:01:49
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = pub-server
TEMPLATE = app

INCLUDEPATH += $(NDDSHOME)/include 
INCLUDEPATH += $(NDDSHOME)/include/ndds

SOURCES += main.cpp \
           pmd-datagen.cpp \
		   pmd.cpp \
		   pmdPlugin.cpp \
		   pmdSupport.cpp \
           mainwindow.cpp

HEADERS  += mainwindow.h pmd-datagen.h pmd.h pmdPlugin.h pmdSupport.h

FORMS    += mainwindow.ui

DEFINES += RTI_UNIX RTI_LINUX RTI_64BIT

LIBS += -L$(NDDSHOME)/lib/$(DDS_ARCH)
LIBS += -lnddscppz -lnddscz -lnddscorez -ldl -lnsl -lm -lpthread -lrt
