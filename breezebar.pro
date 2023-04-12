QT += quick \
    widgets

SOURCES += \
    application/applicationimageprovider.cpp \
    application/applicationmodule.cpp \
    application/applicationmodule_win.cpp \
    application/applicationresult.cpp \
    searchengine/searchengine.cpp \
    searchengine/searchenginemodel.cpp \
    searchengine/searchindex.cpp \
    searchengine/searchmodule.cpp \
    searchengine/searchnode.cpp \
    searchengine/searchresult.cpp \
    main.cpp \
    searchengine/tokennode.cpp \
    searchengine/trienode.cpp \
    setting/settingimageprovider.cpp \
    setting/settingmodule.cpp \
    setting/settingmodule_win.cpp \
    setting/settingresult.cpp \
    setting/settingresult_win.cpp

win32 {
SOURCES += \
    application/applicationmodule_win.cpp \
    application/applicationresult_win.cpp \
    setting/settingmodule_win.cpp
}

resources.files = main.qml 
resources.prefix = /$${TARGET}
RESOURCES += resources \
    breezebar.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    application/applicationimageprovider.h \
    application/applicationmodule.h \
    application/applicationresult.h \
    searchengine/searchengine.h \
    searchengine/searchenginemodel.h \
    searchengine/searchindex.h \
    searchengine/searchmodule.h \
    searchengine/searchnode.h \
    searchengine/searchresult.h \
    searchengine/tokennode.h \
    searchengine/trienode.h \
    setting/settingimageprovider.h \
    setting/settingmodule.h \
    setting/settingresult.h

# ensures that imports don't need to include the name of the module
INCLUDEPATH += \
    searchengine/ \
    application/ \
    setting/ \

DISTFILES += \
    Style.js \
    application/ApplicationResult.qml \
    setting/SettingResult.qml \
    bgui/BButton.qml


# install QHotkey with qdep
QDEP_DEPENDS += Skycoder42/QHotkey
!load(qdep):error("Failed to load qdep feature")


LIBS += -lole32 -lcomctl32

