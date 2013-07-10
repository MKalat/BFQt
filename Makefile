#############################################################################
# Makefile for building: BF
# Generated by qmake (3.0) (Qt 5.1.0) on: Wt 9. lip 11:48:57 2013
# Project:  BFQt.pro
# Template: app
# Command: F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\bin\qmake.exe -spec win32-msvc2010 -o Makefile BFQt.pro
#############################################################################

MAKEFILE      = Makefile

first: release
install: release-install
uninstall: release-uninstall
QMAKE         = F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\bin\qmake.exe
DEL_FILE      = del
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
COPY          = copy /y
COPY_FILE     = $(COPY)
COPY_DIR      = xcopy /s /q /y /i
INSTALL_FILE  = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = del
SYMLINK       = copy /y
DEL_DIR       = rmdir
MOVE          = move
SUBTARGETS    =  \
		release \
		debug


release: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_first: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-all: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: BFQt.pro F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\win32-msvc2010\qmake.conf F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\spec_pre.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\common\shell-win32.conf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\qconfig.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axbase.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axcontainer.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axserver.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_bootstrap.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_clucene.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_concurrent.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_core.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_declarative.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_designer.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_designercomponents.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_gui.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_help.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_multimedia.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_multimediawidgets.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_network.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_opengl.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_openglextensions.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_platformsupport.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_printsupport.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qml.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qmldevtools.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qmltest.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qtmultimediaquicktools.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_quick.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_quickparticles.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_script.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_scripttools.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_sensors.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_serialport.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_sql.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_svg.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_testlib.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_uitools.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_v8.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_webkit.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_webkitwidgets.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_widgets.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_xml.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_xmlpatterns.pri \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt_functions.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt_config.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\win32-msvc2010\qmake.conf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\spec_post.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\exclusive_builds.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\default_pre.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\default_pre.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\resolve_config.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\default_post.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\rtti.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\warn_on.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\resources.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\moc.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\opengl.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\uic.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\windows.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\testcase_targets.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\exceptions.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\yacc.prf \
		F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\lex.prf \
		BFQt.pro \
		F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Widgets.prl \
		F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Gui.prl \
		F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Core.prl \
		F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/libEGL.prl \
		F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/libGLESv2.prl
	$(QMAKE) -spec win32-msvc2010 -o Makefile BFQt.pro
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\spec_pre.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\common\shell-win32.conf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\qconfig.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axbase.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axcontainer.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_axserver.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_bootstrap.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_clucene.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_concurrent.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_core.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_declarative.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_designer.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_designercomponents.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_gui.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_help.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_multimedia.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_multimediawidgets.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_network.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_opengl.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_openglextensions.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_platformsupport.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_printsupport.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qml.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qmldevtools.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qmltest.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_qtmultimediaquicktools.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_quick.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_quickparticles.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_script.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_scripttools.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_sensors.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_serialport.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_sql.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_svg.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_testlib.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_uitools.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_v8.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_webkit.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_webkitwidgets.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_widgets.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_xml.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\modules\qt_lib_xmlpatterns.pri:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt_functions.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt_config.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\win32-msvc2010\qmake.conf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\spec_post.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\exclusive_builds.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\default_pre.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\default_pre.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\resolve_config.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\default_post.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\rtti.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\warn_on.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\qt.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\resources.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\moc.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\opengl.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\uic.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\win32\windows.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\testcase_targets.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\exceptions.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\yacc.prf:
F:\DEVELOPER\QT\510MSVC201032b\5.1.0\msvc2010\mkspecs\features\lex.prf:
BFQt.pro:
F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Widgets.prl:
F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Gui.prl:
F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/Qt5Core.prl:
F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/libEGL.prl:
F:/DEVELOPER/QT/510MSVC201032b/5.1.0/msvc2010/lib/libGLESv2.prl:
qmake: FORCE
	@$(QMAKE) -spec win32-msvc2010 -o Makefile BFQt.pro

qmake_all: FORCE

make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
	-$(DEL_FILE) BF.exp
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

release-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables:
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables

check: first
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
