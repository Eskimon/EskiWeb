QT += webkit
QT += sql
QT += network
SOURCES += main.cpp \
    mainwindow.cpp \
    preference.cpp \
    mycookiejar.cpp \
    favoris.cpp \
    historique.cpp
HEADERS += mainwindow.h \
    preference.h \
    mycookiejar.h \
    favoris.h \
    historique.h
LIBS += -lqscintilla2
RESOURCES += icones.qrc
