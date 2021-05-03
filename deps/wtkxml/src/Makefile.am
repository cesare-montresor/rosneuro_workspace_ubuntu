AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x

lib_LTLIBRARIES = libwtkxml.la

libwtkxml_includedir=$(includedir)/wtkxml

libwtkxml_include_HEADERS = 	XReader.hpp \
				XType.hpp \
				XDocument.hpp \
				XException.hpp \
				rapidxml.hpp \
				rapidxml_iterators.hpp \
				rapidxml_print.hpp \
				rapidxml_utils.hpp

libwtkxml_la_SOURCES = 		XReader.cpp \
				XTools.cpp \
				XType.cpp \
				XDocument.cpp \
				XException.cpp 

						   
libwtkxml_la_LDFLAGS = 		$(AM_CFLAGS) 	\
		      		-version-info $(CURRENT):$(REVISION):$(AGE) \
		      		-release $(RELEASE)
		      		

#libwtkxml_la_LIBADD =



pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wtkxml.pc
