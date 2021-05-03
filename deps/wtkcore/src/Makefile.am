AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x
lib_LTLIBRARIES = libwtkcore.la

libwtkcore_includedir = $(includedir)/wtkcore

libwtkcore_include_HEADERS = 	Callback.hpp	\
				Core.hpp	\
				Object.hpp	\
				Flags.hpp	\
				Semaphore.hpp	\
				Thread.hpp	\
				Threadrunner.hpp	\
				ThreadSafe.hpp	\
				Time.hpp	\
				Exception.hpp	\
				Item.hpp  	\
				Container.hpp  	\
				Streamer.hpp	\
				Proxy.hpp	\
				wtk_random_utilities.hpp
			    
libwtkcore_la_SOURCES = 	Callback.hpp	\
				Core.cpp	\
				Object.cpp	\
				Flags.hpp	\
				Semaphore.cpp	\
				Thread.cpp	\
				Threadrunner.cpp	\
				ThreadSafe.cpp	\
				Time.cpp	\
				Exception.cpp	\
				Item.cpp  	\
				Container.cpp   \
				Streamer.cpp	\
				Proxy.hpp	\
				wtk_random_utilities.cpp
		      
libwtkcore_la_LDFLAGS = 	$(AM_CFLAGS) 	\
		      		-version-info $(CURRENT):$(REVISION):$(AGE) \
		      		-release $(RELEASE)

#libwtkcore_la_LIBADD   =

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = wtkcore.pc

