TEMPLATE = app
TARGET = pa5
INCLUDEPATH += .

CONFIG+=c++2a

# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += ballistic.cpp \
    route.cpp \
    ufo.cpp \
    ufosim.cpp \
    ui_main.cpp \
    vertical.cpp

QT += widgets

HEADERS += ballistic.h \
    route.h \
    ufo.h \
    ufosim.h \
    ui_widget.h \
    ui_window.h \
    vertical.h \
    vertical_thread.h

DISTFILES +=