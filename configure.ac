#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([bitfield-io], [0.6.0], [vitalie@ciubotaru.tk])
AC_CONFIG_SRCDIR([bitfield-io.c])
AC_ARG_WITH([local-bitfield], AS_HELP_STRING([--with-local-bitfield], [Ignore system bitfield library and build local]), [], [])
AC_CONFIG_HEADERS([config.h])

if test "x$prefix" = "xNONE" ; then
  prefix="/usr/local"
fi
if test "x$exec_prefix" = "xNONE" ; then
  exec_prefix=$prefix
fi
PREFIX=$prefix
AC_SUBST([PREFIX])
AC_SUBST([exec_prefix])
# Checks for programs.
AC_PROG_CC([gcc pcc icc])
AC_PROG_LN_S
AC_PROG_MAKE_SET

# Check for system-wide bitfield
AC_SEARCH_LIBS([bfnew], [bitfield], [AC_SUBST(HAVE_BITFIELD, 1)], [AC_SUBST(HAVE_BITFIELD, 0)], [])

# Check if --with_local_bitfield was passed
AS_IF([test "x$with_local_bitfield" = "xyes"],
  # if yes, ignore system-wide bitfield
  AC_SUBST(HAVE_BITFIELD, 0),
  # otherwise check whether system-wide bitfield was found and building local bitfield was explicitly prohibited
  AS_IF([test "x$with_local_bitfield" = "xno" && test "$HAVE_BITFIELD" = 0],
    AC_MSG_ERROR([bitfield library not found]),
  )
)

# Checks for header files.
AC_CHECK_HEADERS(limits.h stdlib.h string.h bitfield.h)

# Checks for typedefs, structures, and compiler characteristics.
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC

#AC_CONFIG_FILES([Makefile])
#AC_OUTPUT([Makefile] [tests/Makefile] [man/Makefile] [examples/Makefile])
AC_OUTPUT([Makefile] [tests/Makefile] [man/Makefile])
