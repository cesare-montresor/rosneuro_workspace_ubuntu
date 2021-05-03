AM_CXXFLAGS = $(CXXFLAGS) -I$(top_srcdir)/src -std=c++0x

noinst_PROGRAMS = test-task test-taskset test-taskset-xml test-events test-events-xml test-timings test-timings-xml

test_task_SOURCES = test-task.cpp
test_task_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore

test_taskset_SOURCES = test-taskset.cpp
test_taskset_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore

test_taskset_xml_SOURCES = test-taskset-xml.cpp
test_taskset_xml_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore -lwtkxml

test_events_SOURCES = test-events.cpp
test_events_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore

test_events_xml_SOURCES = test-events-xml.cpp
test_events_xml_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore -lwtkxml

test_timings_SOURCES = test-timings.cpp
test_timings_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore

test_timings_xml_SOURCES = test-timings-xml.cpp
test_timings_xml_LDADD = $(top_builddir)/src/libwtkprotocol.la -lwtkcore -lwtkxml

TESTS = test-task test-taskset test-taskset-xml test-events test-events-xml test-timings test-timings-xml
