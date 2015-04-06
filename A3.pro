# #####################################################################
# Automatically generated by qmake (2.01a) Tue May 12 19:26:45 2009
# #####################################################################
TEMPLATE = app
TARGET = qtimageskel
DEPENDPATH += .
INCLUDEPATH += .

# Input
HEADERS += glwidget.h \
    window.h \
    foundation.h \
    version.h \ 
    common.h \
    raytracer.h \
    scene.h \
    surface.h \
    ray.h \
    shape.h \
    sphere.h \
    rgb.h \
    color.h

FORMS += MainWindow.ui 

SOURCES += glwidget.cpp \
    main.cpp \
    window.cpp \
    raytracer.cpp \
    scene.cpp \
    surface.cpp \
    ray.cpp \
    shape.cpp \
    sphere.cpp \
    rgb.cpp \
    color.cpp


QT += opengl
