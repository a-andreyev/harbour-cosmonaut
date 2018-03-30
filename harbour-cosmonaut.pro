# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = harbour-cosmonaut

CONFIG += sailfishapp

QT += systeminfo

SOURCES += src/harbour-cosmonaut.cpp \
    src/api/qtrestrocketapi.cpp \
    src/api/models/coolfeedmodel.cpp

OTHER_FILES += \
    rpm/harbour-cosmonaut.changes.in \
    rpm/harbour-cosmonaut.spec \
    rpm/harbour-cosmonaut.yaml \
    translations/*.ts \
    harbour-cosmonaut.desktop

DISTFILES += \
    qml/harbour-cosmonaut.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FeedPage.qml \
    qml/pages/components/IconTextButton.qml \
    qml/pages/AboutPage.qml \
    qml/pages/LoginPage.qml \
    qml/pages/AuthPage.qml \
    qml/pages/components/FeedListItem.qml \
    qml/assets/images/rocket.svg \
    qml/assets/images/aa13q.jpeg \
    qml/assets/images/le_me.jpeg \
    qml/assets/images/flattr.svg \
    qml/assets/images/git.svg \
    qml/assets/images/paypal.svg \
    qml/assets/images/rocketbank.svg \
    qml/assets/rocketbank.ogg


SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

TRANSLATIONS += translations/harbour-cosmonaut-ru.ts

HEADERS += \
    src/api/qtrestrocketapi.h \
    src/api/models/coolfeedmodel.h

#AdCtl: Google Analytics, AdMob, StartAD.mobi, Qt-REST
include(src/3rd/qtrest/com_github_kafeg_qtrest.pri)
