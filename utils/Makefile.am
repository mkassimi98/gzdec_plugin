# Note: plugindir is set in configure

plugin_LTLIBRARIES = libgstgzdec.la
#plugin010_LTLIBRARIES = libgstgzdec_0_10.la

## Plugin 1

# sources used to compile this plug-in
libgstgzdec_la_SOURCES = gstgzdec.c gstgzdec.h zlibdec.c

# compiler and linker flags used to compile this plugin, set in configure.ac
libgstgzdec_la_CFLAGS = $(GST_CFLAGS)
libgstgzdec_la_LIBADD = $(GST_LIBS) $(ZLIB_LIBS)
libgstgzdec_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
libgstgzdec_la_LIBTOOLFLAGS = --tag=disable-static

## Disabled because too many declarations have altered from 0.10
## Plugin 2

# sources used to compile this plug-in
#libgstgzdec_0_10_la_SOURCES = gstgzdec010.c gstgzdec010.h zlibdec.c

# compiler and linker flags used to compile this plugin, set in configure.ac
#libgstgzdec_0_10_la_CFLAGS = $(GST010_CFLAGS)
#libgstgzdec_0_10_la_LIBADD = $(GST010_LIBS) $(ZLIB_LIBS)
#libgstgzdec_0_10_la_LDFLAGS = $(GST_PLUGIN_LDFLAGS)
#libgstgzdec_0_10_la_LIBTOOLFLAGS = --tag=disable-static

# headers we need but don't want installed
noinst_HEADERS = zlibdec.h
