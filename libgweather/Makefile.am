# we need to build two libraries (one real and one static)
# because we access private symbols from the tests
lib_LTLIBRARIES = libgweather-3.la
noinst_LTLIBRARIES = libgweather-internal-3.la
noinst_PROGRAMS = test_metar test_locations test_sun_moon

AM_CPPFLAGS = 			\
	-DGWEATHER_COMPILATION  \
	-D_XOPEN_SOURCE=700	\
	-D_DEFAULT_SOURCE	\
	$(DEPS_CFLAGS)		\
	-I$(top_srcdir)		\
	-I$(top_builddir)	\
	-I$(srcdir)

AM_CFLAGS = $(WARN_CFLAGS)

gweather_new_headers = \
	gweather.h \
	gweather-location.h gweather-location-entry.h \
	gweather-timezone.h gweather-timezone-menu.h \
	gweather-weather.h gweather-enums.h

libgweatherincdir = $(includedir)/libgweather-3.0/libgweather
libgweatherinc_HEADERS = \
	$(gweather_new_headers)		\
	gweather-enum-types.h		\
	gweather-version.h

gweather_c_sources = \
	gweather.c gweather-private.c \
	gweather-weather.c \
	weather-metar.c weather-iwin.c weather-yahoo.c \
	weather-wx.c weather-yrno.c weather-owm.c \
	weather-sun.c weather-moon.c \
	gweather-location.c \
	gweather-timezone.c \
	gweather-location-entry.c \
	gweather-timezone-menu.c \
	gweather-parser.c

introspection_sources = \
	$(gweather_c_sources) \
	$(gweather_new_headers)

built_introspection_sources = \
	gweather-enum-types.h gweather-enum-types.c

libgweather_internal_3_la_SOURCES = \
	$(gweather_c_sources) \
	$(gweather_new_headers) \
	$(built_introspection_sources) \
	gweather-private.h \
	gweather-parser.h

libgweather_internal_3_la_CPPFLAGS = \
	$(AM_CPPFLAGS)			\
	-DG_LOG_DOMAIN=\"GWeather\"	\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\" \
	-DGWEATHER_XML_LOCATION_DIR=\""$(pkgdatadir)"\"

libgweather_internal_3_la_LIBADD = \
	$(LIBM)		\
	$(DEPS_LIBS)	\
	$(REGEX_LIBS)

libgweather_3_la_SOURCES = 
libgweather_3_la_LIBADD = libgweather-internal-3.la
libgweather_3_la_LDFLAGS = \
	-export-symbols-regex "^gweather_(.*)" \
	-version-info $(LT_VERSION) -no-undefined

test_metar_SOURCES = test_metar.c
test_metar_LDADD = libgweather-internal-3.la $(DEPS_LIBS)

test_locations_SOURCES = test_locations.c
test_locations_LDADD = libgweather-3.la $(DEPS_LIBS)

test_sun_moon_SOURCES = test_sun_moon.c
test_sun_moon_LDADD = libgweather-internal-3.la $(DEPS_LIBS)

gweather-enum-types.h: $(gweather_new_headers)
	$(AM_V_GEN)( cd $(srcdir) && $(GLIB_MKENUMS) --template gweather-enum-types.h.tmpl \
		$(gweather_new_headers) ) > gweather-enum-types.h.tmp \
	&& mv gweather-enum-types.h.tmp gweather-enum-types.h \
	|| rm -f gweather-enum-type.h.tmp

gweather-enum-types.c: $(gweather_new_headers)
	$(AM_V_GEN)( cd $(srcdir) && $(GLIB_MKENUMS) --template gweather-enum-types.c.tmpl \
		$(gweather_new_headers) ) > gweather-enum-types.c.tmp \
	&& mv gweather-enum-types.c.tmp gweather-enum-types.c \
	|| rm -f gweather-enum-type.c.tmp

BUILT_SOURCES = gweather-enum-types.c gweather-enum-types.h

EXTRA_DIST = gweather-version.h.in

CLEANFILES = $(noinst_PROGRAMS) $(BUILT_SOURCES)

# Introspection
-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --warn-all --add-include-path=$(srcdir) --c-include=libgweather/gweather.h
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
GWeather-3.0.gir: libgweather-3.la Makefile
GWeather_3_0_gir_INCLUDES = GObject-2.0 Gtk-3.0
GWeather_3_0_gir_CFLAGS = $(libgweather_internal_3_la_CPPFLAGS)
GWeather_3_0_gir_LIBS = libgweather-3.la
GWeather_3_0_gir_SCANNERFLAGS = --identifier-prefix=GWeather --symbol-prefix=gweather --pkg-export=gweather-3.0
GWeather_3_0_gir_FILES = $(addprefix $(srcdir)/,$(introspection_sources)) $(addprefix $(builddir)/,$(built_introspection_sources))
INTROSPECTION_GIRS += GWeather-3.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)

if ENABLE_VAPIGEN
-include $(VAPIGEN_MAKEFILE)

VAPIGEN_VAPIS = gweather-3.0.vapi

gweather-3.0.vapi: GWeather-3.0.gir
gweather_3_0_vapi_DEPS = gobject-2.0 gtk+-3.0
gweather_3_0_vapi_METADATADIRS = $(srcdir)
gweather_3_0_vapi_VAPIDIRS = $(datadir)/vala/vapi
gweather_3_0_vapi_FILES = GWeather-3.0.gir

vapidir = $(VAPIGEN_VAPIDIR)
nodist_vapi_DATA = $(VAPIGEN_VAPIS)

CLEANFILES += $(nodist_vapi_DATA)

endif # ENABLE_VAPIGEN
endif # HAVE_INTROSPECTION

-include $(top_srcdir)/git.mk
