QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
OBJECTS_DIR = objs/

SOURCES += \
    src/main.cpp \
    src/pervertt_main_frame.cpp \
    src/manual_controls.cpp \

HEADERS += \
  inc/pervertt_main_frame.h \
  inc/manual_controls.h \
  

FORMS += \
    ./ui/pervertt_main_frame.ui

CONFIG += qtc_runnable

INCLUDEPATH += $$PWD/inc \


target.path = /home/testbench/pervertt

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /home/pi/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/DesktopCAN_API/canapi.pri)
