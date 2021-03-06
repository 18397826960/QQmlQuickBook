
CONFIG(debug,debug|release){
    TARGET =   hellowworld_debug
}else{
    TARGET =   hellowworld
}

TEMPLATE = app

QT += gui
QT += core
QT += qml
QT += quick
QT += widgets

include($$PWD/../../QQmlQuickBook.pri)
include($$PWD/../../sstd_utility/sstd_quick.pri)
DESTDIR = $$RootDestDir

SOURCES += $$PWD/main.cpp

SOURCES += $$PWD/RootWindow.cpp
HEADERS += $$PWD/RootWindow.hpp

SOURCES += $$PWD/Application.cpp
HEADERS += $$PWD/Application.hpp

QMLSOURCES += $$PWD/myqml/hellowword/main.qml
QMLSOURCES += $$PWD/myqml/hellowword/main_private/MainText.qml
QMLSOURCES += $$PWD/myqml/hellowword/main_private/MainRectangle.qml

lupdate_only{
    SOURCES += $$QMLSOURCES
}

DISTFILES += $$QMLSOURCES

#force add application dir to library search dir
!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

RESOURCES += $$PWD/../../qqmlquickglobal.qrc

DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"
SOURCES += $$PWD/GetLocalFullPath.cpp

include($$PWD/this/this.pri)

CONFIG(debug,debug|release){
    LIBS += -L$$RootDestDir -lsstd_core_libraryd
    QMAKE_POST_LINK += $$DESTDIR/buildinstall_debug $$PWD "myqml"
    export(QMAKE_POST_LINK)
}else{
    LIBS += -L$$RootDestDir -lsstd_core_library
    QMAKE_POST_LINK += $$DESTDIR/buildinstall $$PWD "myqml"
    export(QMAKE_POST_LINK)
}


