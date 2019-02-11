QT       += network
QT       -= gui

TARGET = qjsonrpc
TEMPLATE = lib

DEFINES += LIBQJSONRPC_LIBRARY

LIBS += -lqhttpserver

DEFINES += QT_DEPRECATED_WARNINGS

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    requesthandler.cpp \
    requesthandlerfactory.cpp \
    jsonrpcserver.cpp \
    jsonrpcresponse.cpp \
    jsonrpcrequest.cpp \
    jsonrpcclient.cpp

HEADERS += \
    libqjsonrpc_global.h \
    requesthandler.h \
    requesthandlerfactory.h \
    jsonrpcserver.h \
    jsonrpcresponse.h \
    jsonrpcrequest.h \
    jsonrpcclient.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
