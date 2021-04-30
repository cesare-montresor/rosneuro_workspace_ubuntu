AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x

noinst_PROGRAMS = test-container 

test_container_SOURCES = test-container.cpp
test_container_LDADD = $(top_builddir)/src/libwtkcore.la


TESTS = test-container
