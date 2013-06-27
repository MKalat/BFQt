#############################################################################
# Makefile for building: BFQt
# Generated by qmake (2.01a) (Qt 4.8.4) on: Cz 27. cze 02:30:42 2013
# Project:  BFQt.pro
# Template: app
# Command: f:\DEVELOPER\QT\4.8.4\bin\qmake.exe -spec f:\DEVELOPER\QT\4.8.4\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile BFQt.pro
#############################################################################

first: release
install: release-install
uninstall: release-uninstall
MAKEFILE      = Makefile
QMAKE         = f:\DEVELOPER\QT\4.8.4\bin\qmake.exe
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
SYMLINK       = 
DEL_DIR       = rmdir
MOVE          = move
CHK_DIR_EXISTS= if not exist
MKDIR         = mkdir
SUBTARGETS    =  \
		release \
		debug

release: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release
release-make_default: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release 
release-make_first: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release first
release-all: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release all
release-clean: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release clean
release-distclean: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release distclean
release-install: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release install
release-uninstall: $(MAKEFILE).Release FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release uninstall
debug: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug
debug-make_default: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug 
debug-make_first: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug first
debug-all: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug all
debug-clean: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug clean
debug-distclean: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug distclean
debug-install: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug install
debug-uninstall: $(MAKEFILE).Debug FORCE
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug uninstall

Makefile: BFQt.pro  f:\DEVELOPER\QT\4.8.4\mkspecs\win32-msvc2008\qmake.conf f:\DEVELOPER\QT\4.8.4\mkspecs\qconfig.pri \
		f:\DEVELOPER\QT\4.8.4\mkspecs\modules\qt_webkit_version.pri \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt_functions.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt_config.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\exclusive_builds.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\default_pre.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\default_pre.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\release.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\debug_and_release.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\default_post.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\default_post.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\rtti.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\exceptions.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\stl.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\shared.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\embed_manifest_exe.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\embed_manifest_dll.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\warn_on.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\thread.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\moc.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\windows.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\resources.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\uic.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\yacc.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\lex.prf \
		f:\DEVELOPER\QT\4.8.4\mkspecs\features\include_source_dir.prf \
		f:\DEVELOPER\QT\4.8.4\lib\qtmain.prl
	$(QMAKE) -spec f:\DEVELOPER\QT\4.8.4\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile BFQt.pro
f:\DEVELOPER\QT\4.8.4\mkspecs\qconfig.pri:
f:\DEVELOPER\QT\4.8.4\mkspecs\modules\qt_webkit_version.pri:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt_functions.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt_config.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\exclusive_builds.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\default_pre.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\default_pre.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\release.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\debug_and_release.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\default_post.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\default_post.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\rtti.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\exceptions.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\stl.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\shared.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\embed_manifest_exe.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\embed_manifest_dll.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\warn_on.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\qt.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\thread.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\moc.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\win32\windows.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\resources.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\uic.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\yacc.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\lex.prf:
f:\DEVELOPER\QT\4.8.4\mkspecs\features\include_source_dir.prf:
f:\DEVELOPER\QT\4.8.4\lib\qtmain.prl:
qmake: qmake_all FORCE
	@$(QMAKE) -spec f:\DEVELOPER\QT\4.8.4\mkspecs\win32-msvc2008 CONFIG+=release -o Makefile BFQt.pro

qmake_all: FORCE

make_default: release-make_default debug-make_default FORCE
make_first: release-make_first debug-make_first FORCE
all: release-all debug-all FORCE
clean: release-clean debug-clean FORCE
	-$(DEL_FILE) ".\BFQt.intermediate.manifest"
	-$(DEL_FILE) BFQt.exp
distclean: release-distclean debug-distclean FORCE
	-$(DEL_FILE) Makefile

check: first

release-mocclean: $(MAKEFILE).Release
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocclean
debug-mocclean: $(MAKEFILE).Debug
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocclean
mocclean: release-mocclean debug-mocclean

release-mocables: $(MAKEFILE).Release
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Release mocables
debug-mocables: $(MAKEFILE).Debug
	@set MAKEFLAGS=$(MAKEFLAGS)
	$(MAKE) -f $(MAKEFILE).Debug mocables
mocables: release-mocables debug-mocables
FORCE:

$(MAKEFILE).Release: Makefile
$(MAKEFILE).Debug: Makefile
