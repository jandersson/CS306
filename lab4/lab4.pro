TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    lab4-client.c \
    lab4-server.c

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    makefile

