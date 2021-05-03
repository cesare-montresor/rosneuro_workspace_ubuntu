/* config/config.h.  Generated from config.h.in by configure.  */
/* config/config.h.in.  Generated from configure.ac by autoheader.  */

/* attribute of the symbols exported in the API */
#define API_EXPORTED __attribute__ ((visibility ("default")))

/* read-only architecture-independent data path */
#define DATADIR "/usr/local/share"

/* Define to disable the glib checks */
#define G_DISABLE_CAST_CHECKS /**/

/* Define to 1 if the system has the type `clockid_t'. */
#define HAVE_CLOCKID_T 1

/* Define to 1 if you have the `clock_gettime' function. */
#define HAVE_CLOCK_GETTIME 1

/* Define to 1 if you have the `clock_nanosleep' function. */
#define HAVE_CLOCK_NANOSLEEP 1

/* Define to 1 if you have the declaration of `clock_gettime', and to 0 if you
   don't. */
#define HAVE_DECL_CLOCK_GETTIME 1

/* Define to 1 if you have the declaration of `clock_nanosleep', and to 0 if
   you don't. */
#define HAVE_DECL_CLOCK_NANOSLEEP 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the `ftime' function. */
#define HAVE_FTIME 1

/* Define to 1 if GetSystemTimeAsFileTime is present */
/* #undef HAVE_GETSYSTEMTIMEASFILETIME */

/* Define to 1 if you have the `gettimeofday' function. */
#define HAVE_GETTIMEOFDAY 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if the system has the type `struct timespec'. */
#define HAVE_STRUCT_TIMESPEC 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 or 0, depending whether the compiler supports simple visibility
   declarations. */
#define HAVE_VISIBILITY 1

/* Define to 1 if you have the `_ftime' function. */
/* #undef HAVE__FTIME */

/* attribute of the non-exported symbols */
#define LOCAL_FN __attribute__ ((visibility ("hidden")))

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* Name of package */
#define PACKAGE "mcpanel"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "nicolas.bourdaud@gmail.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "mcpanel"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "mcpanel 0.0"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "mcpanel"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.0"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.0"
