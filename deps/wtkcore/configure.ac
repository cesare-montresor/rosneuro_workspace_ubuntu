# - If the library source code has changed at all since the last update,
# then increment revision.
# - If any interfaces have been added, removed, or changed since the last
# update, increment current, and set revision to 0.
# - If any interfaces have been added since the last public release, then
# increment age.
# - If any interfaces have been removed since the last public release, then
# set age to 0.

m4_define([lib_release],0)
m4_define([lib_current],1)
m4_define([lib_revision],0)
m4_define([lib_age],0)

m4_define([packageversion], [lib_release.lib_current.lib_age.lib_revision[]b])

# Setup Automake
AC_INIT(wtkcore,[packageversion],luca.tonin@dei.unipd.it)
AC_CONFIG_SRCDIR([src/Core.hpp])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_HEADERS([config/config.h])

# Initialize Automake
AM_INIT_AUTOMAKE([subdir-objects no-dist-gzip dist-bzip2 color-tests])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD
AC_LANG_CPLUSPLUS
# Checks for programs.
AC_PROG_LIBTOOL
AC_PROG_CXX
LT_INIT([win32-dll disable-static])
AC_SUBST(LIBTOOL_DEPS)

AC_HEADER_STDBOOL

# pthread is needed in core and modules
AC_SEARCH_LIBS([pthread_create], [pthread posix4], [],
               AC_MSG_ERROR([The pthread library has not been found]))

AC_SUBST([RELEASE], [lib_release])
AC_SUBST([CURRENT],[lib_current])
AC_SUBST([REVISION],[lib_revision])
AC_SUBST([AGE],[lib_age])
AC_SUBST(AM_LDFLAGS)

AC_CONFIG_FILES([Makefile src/Makefile src/wtkcore.pc tests/Makefile debug/Makefile])
AC_OUTPUT

