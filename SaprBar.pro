QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG += static
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    myfunc.cpp \
    myrect.cpp \
    node.cpp \
    postprocessor.cpp \
    preproccessor.cpp \
    processor.cpp \
    sealing.cpp \
    tablestructures.cpp \
    validatedcellwidget.cpp

HEADERS += \
    mainwindow.h \
    myfunc.h \
    myrect.h \
    node.h \
    postprocessor.h \
    preproccessor.h \
    processor.h \
    sealing.h \
    tablestructures.h \
    validatedcellwidget.h

FORMS += \
    mainwindow.ui \
    postprocessor.ui \
    preproccessor.ui \
    processor.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Красный стрелочки.png \
    Красный стрелочки.png \
    Синий стрелочки.png

RESOURCES += \
    Pictures.qrc
