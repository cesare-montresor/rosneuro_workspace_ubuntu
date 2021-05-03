AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x

lib_LTLIBRARIES = libwtkprotocol.la

libwtkprotocol_includedir = $(includedir)/wtkprotocol

libwtkprotocol_include_HEADERS = Task.hpp \
				 TaskSet.hpp \
				 Events.hpp \
				 Timings.hpp \
				 wtk_protocol_utilities.hpp
				
			    
libwtkprotocol_la_SOURCES = 	Task.cpp \
				TaskSet.cpp \
				Events.cpp \
				Timings.cpp \
				wtk_protocol_utilities.hpp
				
		      
libwtkprotocol_la_LDFLAGS = 	$(AM_CFLAGS) 	\
		      		-version-info $(CURRENT):$(REVISION):$(AGE) \
		      		-release $(RELEASE)
		      		
libwtkprotocol_la_LIBADD = -lwtkcore -lwtkxml


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wtkprotocol.pc

