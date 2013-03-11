TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    gaussJordan.c \
    matrizes.c

HEADERS += \
    gaussJordan.h \
    util.h \
    fatoracaoLU.h \
    matriz.h

