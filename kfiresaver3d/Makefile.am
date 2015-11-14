####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kfiresaver3d

## INCLUDES were found outside kdevelop specific part

kfiresaver3d_SOURCES = kfiresaversetup.ui particle.cpp main.cpp kfiresaverkss.cpp kfiresaver.cpp 
kfiresaver3d_LDADD   = -lkscreensaver $(LIB_QT) $(LIBSOCKET)


EXTRA_DIST = fw_explode.wav kde.png kfiresaver.cpp kfiresaver.h kfiresaverkss.cpp kfiresaverkss.h main.cpp particle.bmp particle.cpp particle.h tux.png kfiresaversetup.ui kfiresaver3D.desktop 

install-data-local:
	$(mkinstalldirs) $(kde_datadir)/kfiresaver/
	$(INSTALL_DATA) $(srcdir)/fw_explode.wav $(kde_datadir)/kfiresaver/fw_explode.wav
	$(mkinstalldirs) $(kde_datadir)/kfiresaver/
	$(INSTALL_DATA) $(srcdir)/kde.png $(kde_datadir)/kfiresaver/kde.png
	$(mkinstalldirs) $(kde_datadir)/kfiresaver/
	$(INSTALL_DATA) $(srcdir)/particle.bmp $(kde_datadir)/kfiresaver/particle.bmp
	$(mkinstalldirs) $(kde_datadir)/kfiresaver/
	$(INSTALL_DATA) $(srcdir)/tux.png $(kde_datadir)/kfiresaver/tux.png
	$(mkinstalldirs) $(kde_appsdir)/System/
	$(INSTALL_DATA) $(srcdir)/kfiresaver3D.desktop $(kde_appsdir)/System/ScreenSavers

uninstall-local:
	-rm -f $(kde_datadir)/kfiresaver/fw_explode.wav
	-rm -f $(kde_datadir)/kfiresaver/kde.png
	-rm -f $(kde_datadir)/kfiresaver/particle.bmp
	-rm -f $(kde_datadir)/kfiresaver/tux.png
	-rm -f $(kde_appsdir)/System/ScreenSavers

####### kdevelop will overwrite this part!!! (end)############
# These paths are KDE specific. Use them:
# kde_appsdir         Where your application's menu entry (.desktop) should go to.
# kde_icondir         Where your icon should go to - better use KDE_ICON.
# kde_sounddir        Where your sounds should go to.
# kde_htmldir         Where your docs should go to. (contains lang subdirs)
# kde_datadir         Where you install application data. (Use a subdir)
# kde_locale          Where translation files should go to. (contains lang subdirs)
# kde_cgidir          Where cgi-bin executables should go to.
# kde_confdir         Where config files should go to (system-wide ones with default values).
# kde_mimedir         Where mimetypes .desktop files should go to.
# kde_servicesdir     Where services .desktop files should go to.
# kde_servicetypesdir Where servicetypes .desktop files should go to.
# kde_toolbardir      Where general toolbar icons should go to (deprecated, use KDE_ICON).
# kde_wallpaperdir    Where general wallpapers should go to.
# kde_templatesdir    Where templates for the "New" menu (Konqueror/KDesktop) should go to.
# kde_bindir          Where executables should go to. Use bin_PROGRAMS or bin_SCRIPTS.
# kde_libdir          Where shared libraries should go to. Use lib_LTLIBRARIES.
# kde_moduledir       Where modules (e.g. parts) should go to. Use kde_module_LTLIBRARIES.
# kde_styledir        Where Qt/KDE widget styles should go to (new in KDE 3).
# kde_designerdir     Where Qt Designer plugins should go to (new in KDE 3).

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)

METASOURCES = AUTO

# the library search path. 
kfiresaver3d_LDFLAGS = $(all_libraries) $(KDE_RPATH)

# Uncomment the following two lines if you add a ui.rc file for your application to make use of
# KDE´s XML GUI builing
#rcdir = $(kde_datadir)/kfiresaver3d
#rc_DATA = kfiresaver3dui.rc

#WARNING: if you use a ui.rc file above, use:

# messages: rc.cpp

# instead of 

# messages:

messages: 
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kfiresaver3d.pot; \
	fi

