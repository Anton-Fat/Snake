QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    include/animal.cpp \
    include/example.cpp \
    include/map.cpp \
    include/player.cpp \
    include/python.cpp \
    main.cpp \
    snake.cpp

HEADERS += \
    include/animal.h \
    include/map.h \
    include/player.h \
    include/python.h \
    snake.h

RESOURCES += \
    Res.qrc
    # Includes =====================================================================

    INCLUDEPATH += \
        $${PWD}/include \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



