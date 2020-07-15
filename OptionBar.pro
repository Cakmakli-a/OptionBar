CONFIG += qt debug rtti thread exceptions c++14
QT += core gui widgets
CONFIG -= qml_debug

TEMPLATE = app
TARGET = optionbar

HEADERS += \
           optionbar.hpp
SOURCES += main.cpp \
           optionbar.cpp
