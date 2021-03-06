CONFIG(debug,debug|release){
    TARGET =   chat_debug
}else{
    TARGET =   chat
}

TEMPLATE = app

QT += gui
QT += qml
QT += core
QT += quick
QT += widgets
QT += concurrent

QT += gui_private
QT += core_private
QT += widgets_private

include($$PWD/../../QQmlQuickBook.pri)
DESTDIR = $$RootDestDir

DISTFILES +=

#force add application dir to library search dir
!win32 {
    QMAKE_LFLAGS += -Wl,-rpath .
}

RESOURCES += \
    chatsource/chatqmlsource.qrc

SOURCES += $$PWD/Application.cpp \
    $$PWD/QmlApplicationEngine.cpp \
    $$PWD/chatsource/qml_chat_qtextdocumentlayout.cpp \
    $$PWD/chatsource/TextFrameItem.cpp \
    $$PWD/chatsource/ChatView.cpp \
    $$PWD/chatsource/ChatImageProvider.cpp \
    $$PWD/chatsource/ChatSimpleReply.cpp \
    $$PWD/chatsource/ChatSimpleRequest.cpp

SOURCES += $$PWD/GetLocalFullPath.cpp
SOURCES += $$PWD/main.cpp

HEADERS += $$PWD/Application.hpp \
    $$PWD/QmlApplicationEngine.hpp \
    $$PWD/chatsource/qml_chat_qtextdocumentlayout_p.h \
    $$PWD/chatsource/TextFrameItem.hpp \
    $$PWD/chatsource/ChatView.hpp \
    $$PWD/chatsource/ChatViewPrivate.hpp \
    $$PWD/chatsource/ChatImageProvider.hpp \
    $$PWD/chatsource/ChatDocumentLayout.hpp \
    $$PWD/chatsource/ChatSimpleReply.hpp \
    $$PWD/chatsource/ChatSimpleRequest.hpp

QMLSOURCES += $$PWD/myqml/chat/main.qml

lupdate_only{
    SOURCES += $$QMLSOURCES
}

DEFINES += CURRENT_DEBUG_PATH=\\\"$$PWD\\\"

RESOURCES += $$PWD/../../qqmlquickglobal.qrc

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

