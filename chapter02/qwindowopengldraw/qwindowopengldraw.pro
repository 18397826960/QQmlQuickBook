TARGET = $$qtLibraryTarget(qwindowopengldraw)
TEMPLATE = app

QT += gui
QT += qml
QT += core
QT += quick
QT += widgets
QT += concurrent

include($$PWD/../../QQmlQuickBook.pri)
DESTDIR = $$RootDestDir

#buildinstall
QMAKE_POST_LINK += $$DESTDIR/$$qtLibraryTarget(buildinstall) $$PWD "myqml"
export(QMAKE_POST_LINK)

DISTFILES += $$PWD/myqml/qwindowopengldraw/fragment.frag \
    $$PWD/myqml/qwindowopengldraw/vertex.vert

#force add application dir to library search dir
!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

RESOURCES += $$PWD/../../qqmlquickglobal.qrc

SOURCES += $$PWD/main.cpp \
    $$PWD/Application.cpp \
    $$PWD/OpenGLWindow.cpp

HEADERS += \
    $$PWD/Application.hpp \
    $$PWD/OpenGLWindow.hpp

include($$PWD/../../sstd_utility/glew.pri)
include($$PWD/../../sstd_utility/glm.pri)
