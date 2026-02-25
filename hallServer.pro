QT += core network
QT -= gui
# Убираем testlib, так как собираем сервер, а не тесты
QT -= testlib

CONFIG += c++17 console
CONFIG -= app_bundle

TARGET = hallServer
TEMPLATE = app

HEADERS += myserver.h heapsorter.h

# Включаем main.cpp (точку входа сервера) и отключаем тесты
SOURCES += main.cpp
# SOURCES += tst_solver.cpp
