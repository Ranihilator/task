# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/GNU-Linux
TARGET = chat
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += link_pkgconfig debug 
PKGCONFIG += Qt5Qml breakpad breakpad-client
QT = core gui widgets network opengl
SOURCES += src/gui.cpp src/main.cpp src/test.cpp
HEADERS += include/defines.h include/gui.h include/test.h
FORMS +=
RESOURCES += ui/main.qrc
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/GNU-Linux
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += include /media/Store/Incoming/boost_1_67_0 
LIBS += -ldl  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++14
}
