#############################################################################
# Makefile for building: EskiWeb
# Generated by qmake (2.01a) (Qt 4.6.3) on: sam. juil. 10 12:11:57 2010
# Project:  EskiWeb.pro
# Template: app
# Command: /home/eskimon/qtsdk-2010.03/qt/bin/qmake -spec ../../qtsdk-2010.03/qt/mkspecs/linux-g++ -unix -o Makefile EskiWeb.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_WEBKIT_LIB -DQT_SQL_LIB -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I../../qtsdk-2010.03/qt/mkspecs/linux-g++ -I. -I../../qtsdk-2010.03/qt/include/QtCore -I../../qtsdk-2010.03/qt/include/QtNetwork -I../../qtsdk-2010.03/qt/include/QtGui -I../../qtsdk-2010.03/qt/include/QtSql -I../../qtsdk-2010.03/qt/include/QtWebKit -I../../qtsdk-2010.03/qt/include -I.
LINK          = g++
LFLAGS        = -Wl,-O1 -Wl,-rpath,/home/eskimon/qtsdk-2010.03/qt/lib
LIBS          = $(SUBLIBS)  -L/home/eskimon/qtsdk-2010.03/qt/lib -lqscintilla2 -lQtWebKit -L/home/eskimon/qtsdk-2010.03/qt/lib -L/usr/X11R6/lib -lphonon -L/home/berlin/dev/qt-4.6.3-opensource-shipping/this_path_is_supposed_to_be_very_long_hopefully_this_is_long_enough/qt/lib -lQtDBus -lQtXml -lQtXmlPatterns -lQtSql -lQtGui -lQtNetwork -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /home/eskimon/qtsdk-2010.03/qt/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		preference.cpp \
		mycookiejar.cpp \
		favoris.cpp \
		historique.cpp moc_mainwindow.cpp \
		moc_preference.cpp \
		moc_mycookiejar.cpp \
		moc_favoris.cpp \
		moc_historique.cpp \
		qrc_icones.cpp
OBJECTS       = main.o \
		mainwindow.o \
		preference.o \
		mycookiejar.o \
		favoris.o \
		historique.o \
		moc_mainwindow.o \
		moc_preference.o \
		moc_mycookiejar.o \
		moc_favoris.o \
		moc_historique.o \
		qrc_icones.o
DIST          = ../../qtsdk-2010.03/qt/mkspecs/common/g++.conf \
		../../qtsdk-2010.03/qt/mkspecs/common/unix.conf \
		../../qtsdk-2010.03/qt/mkspecs/common/linux.conf \
		../../qtsdk-2010.03/qt/mkspecs/qconfig.pri \
		../../qtsdk-2010.03/qt/mkspecs/features/qt_functions.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/qt_config.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/exclusive_builds.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/default_pre.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/release.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/default_post.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/warn_on.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/qt.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/unix/thread.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/moc.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/resources.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/uic.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/yacc.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/lex.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/include_source_dir.prf \
		EskiWeb.pro
QMAKE_TARGET  = EskiWeb
DESTDIR       = 
TARGET        = EskiWeb

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: EskiWeb.pro  ../../qtsdk-2010.03/qt/mkspecs/linux-g++/qmake.conf ../../qtsdk-2010.03/qt/mkspecs/common/g++.conf \
		../../qtsdk-2010.03/qt/mkspecs/common/unix.conf \
		../../qtsdk-2010.03/qt/mkspecs/common/linux.conf \
		../../qtsdk-2010.03/qt/mkspecs/qconfig.pri \
		../../qtsdk-2010.03/qt/mkspecs/features/qt_functions.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/qt_config.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/exclusive_builds.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/default_pre.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/release.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/default_post.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/warn_on.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/qt.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/unix/thread.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/moc.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/resources.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/uic.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/yacc.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/lex.prf \
		../../qtsdk-2010.03/qt/mkspecs/features/include_source_dir.prf \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtWebKit.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libphonon.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtDBus.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtXml.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtCore.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtGui.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtXmlPatterns.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtNetwork.prl \
		/home/eskimon/qtsdk-2010.03/qt/lib/libQtSql.prl
	$(QMAKE) -spec ../../qtsdk-2010.03/qt/mkspecs/linux-g++ -unix -o Makefile EskiWeb.pro
../../qtsdk-2010.03/qt/mkspecs/common/g++.conf:
../../qtsdk-2010.03/qt/mkspecs/common/unix.conf:
../../qtsdk-2010.03/qt/mkspecs/common/linux.conf:
../../qtsdk-2010.03/qt/mkspecs/qconfig.pri:
../../qtsdk-2010.03/qt/mkspecs/features/qt_functions.prf:
../../qtsdk-2010.03/qt/mkspecs/features/qt_config.prf:
../../qtsdk-2010.03/qt/mkspecs/features/exclusive_builds.prf:
../../qtsdk-2010.03/qt/mkspecs/features/default_pre.prf:
../../qtsdk-2010.03/qt/mkspecs/features/release.prf:
../../qtsdk-2010.03/qt/mkspecs/features/default_post.prf:
../../qtsdk-2010.03/qt/mkspecs/features/warn_on.prf:
../../qtsdk-2010.03/qt/mkspecs/features/qt.prf:
../../qtsdk-2010.03/qt/mkspecs/features/unix/thread.prf:
../../qtsdk-2010.03/qt/mkspecs/features/moc.prf:
../../qtsdk-2010.03/qt/mkspecs/features/resources.prf:
../../qtsdk-2010.03/qt/mkspecs/features/uic.prf:
../../qtsdk-2010.03/qt/mkspecs/features/yacc.prf:
../../qtsdk-2010.03/qt/mkspecs/features/lex.prf:
../../qtsdk-2010.03/qt/mkspecs/features/include_source_dir.prf:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtWebKit.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libphonon.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtDBus.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtXml.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtCore.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtGui.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtXmlPatterns.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtNetwork.prl:
/home/eskimon/qtsdk-2010.03/qt/lib/libQtSql.prl:
qmake:  FORCE
	@$(QMAKE) -spec ../../qtsdk-2010.03/qt/mkspecs/linux-g++ -unix -o Makefile EskiWeb.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/EskiWeb1.0.0 || $(MKDIR) .tmp/EskiWeb1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/EskiWeb1.0.0/ && $(COPY_FILE) --parents mainwindow.h preference.h mycookiejar.h favoris.h historique.h .tmp/EskiWeb1.0.0/ && $(COPY_FILE) --parents icones.qrc .tmp/EskiWeb1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp preference.cpp mycookiejar.cpp favoris.cpp historique.cpp .tmp/EskiWeb1.0.0/ && (cd `dirname .tmp/EskiWeb1.0.0` && $(TAR) EskiWeb1.0.0.tar EskiWeb1.0.0 && $(COMPRESS) EskiWeb1.0.0.tar) && $(MOVE) `dirname .tmp/EskiWeb1.0.0`/EskiWeb1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/EskiWeb1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_preference.cpp moc_mycookiejar.cpp moc_favoris.cpp moc_historique.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_preference.cpp moc_mycookiejar.cpp moc_favoris.cpp moc_historique.cpp
moc_mainwindow.cpp: preference.h \
		mainwindow.h \
		mycookiejar.h \
		favoris.h \
		mainwindow.h
	/home/eskimon/qtsdk-2010.03/qt/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_preference.cpp: mainwindow.h \
		preference.h \
		mycookiejar.h \
		favoris.h \
		preference.h
	/home/eskimon/qtsdk-2010.03/qt/bin/moc $(DEFINES) $(INCPATH) preference.h -o moc_preference.cpp

moc_mycookiejar.cpp: mycookiejar.h
	/home/eskimon/qtsdk-2010.03/qt/bin/moc $(DEFINES) $(INCPATH) mycookiejar.h -o moc_mycookiejar.cpp

moc_favoris.cpp: favoris.h
	/home/eskimon/qtsdk-2010.03/qt/bin/moc $(DEFINES) $(INCPATH) favoris.h -o moc_favoris.cpp

moc_historique.cpp: historique.h
	/home/eskimon/qtsdk-2010.03/qt/bin/moc $(DEFINES) $(INCPATH) historique.h -o moc_historique.cpp

compiler_rcc_make_all: qrc_icones.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_icones.cpp
qrc_icones.cpp: icones.qrc \
		icones_prog/EskiNet_Logo.ico
	/home/eskimon/qtsdk-2010.03/qt/bin/rcc -name icones icones.qrc -o qrc_icones.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		preference.h \
		mycookiejar.h \
		favoris.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		preference.h \
		mycookiejar.h \
		favoris.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

preference.o: preference.cpp preference.h \
		mainwindow.h \
		mycookiejar.h \
		favoris.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o preference.o preference.cpp

mycookiejar.o: mycookiejar.cpp mycookiejar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mycookiejar.o mycookiejar.cpp

favoris.o: favoris.cpp favoris.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o favoris.o favoris.cpp

historique.o: historique.cpp historique.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o historique.o historique.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_preference.o: moc_preference.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_preference.o moc_preference.cpp

moc_mycookiejar.o: moc_mycookiejar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mycookiejar.o moc_mycookiejar.cpp

moc_favoris.o: moc_favoris.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_favoris.o moc_favoris.cpp

moc_historique.o: moc_historique.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_historique.o moc_historique.cpp

qrc_icones.o: qrc_icones.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_icones.o qrc_icones.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

