QT       += testlib

QT       -= gui
QT       += network
LIBS += -lqhttpserver


TARGET = tst_jsonrpcserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000


SOURCES += \
        tst_jsonrpcserver.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../libqjsonrpc/release/ -lqjsonrpc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../libqjsonrpc/debug/ -lqjsonrpc
else:unix: LIBS += -L$$OUT_PWD/../libqjsonrpc/ -lqjsonrpc

INCLUDEPATH += $$PWD/../libqjsonrpc
DEPENDPATH += $$PWD/../libqjsonrpc
