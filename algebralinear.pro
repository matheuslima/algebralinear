TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    gaussJordan.c \
    matriz.c \
    fatoracaoLU.c

HEADERS += \
    gaussJordan.h \
    util.h \
    fatoracaoLU.h \
    matriz.h

