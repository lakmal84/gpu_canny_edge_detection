# Process this file with autoconf to produce a configure script.
AC_INIT([gpu_canny_edge_detection], [2.0], [lakmal84@gmail.com])
AC_CONFIG_SRCDIR([src/edge.cpp])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS(opencv2/opencv.hpp, opencv2/core/core.hpp, opencv2/highgui/highgui.hpp, opencv2/imgproc/imgproc.hpp)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_MEMCMP
AC_HEADER_STDC
AC_CHECK_FUNCS

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
