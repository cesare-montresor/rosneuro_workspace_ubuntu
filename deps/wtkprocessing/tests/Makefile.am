AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x

noinst_PROGRAMS = test-csp

test_csp_SOURCES = test-csp.cpp
test_csp_LDADD = $(top_builddir)/src/libwtkprocessing.la -lwtkcore

TESTS = test-csp
