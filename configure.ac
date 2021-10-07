
## Process this file with autoconf to produce a configure script.
##
## Configure.ac for RcppGSL
##
## Copyright (C) 2010         Romain Francois and Dirk Eddelbuettel
## Copyright (C) 2014 - 2021  Dirk Eddelbuettel
##
## Licensed under GNU GPL 2 or later

# The version set here will propagate to other files from here
## Process this file with autoconf to produce a configure script.
AC_INIT([RcppGSL],[0.3.10],[edd@debian.org])

# Checks for common programs using default macros
AC_PROG_CC

## Use gsl-config to find arguments for compiler and linker flags
##
## Check for non-standard programs: gsl-config(1)
AC_PATH_PROG([GSL_CONFIG], [gsl-config])
## If gsl-config was found, let's use it
if test "${GSL_CONFIG}" != ""; then
    # Use gsl-config for header and linker arguments
    GSL_CFLAGS=`${GSL_CONFIG} --cflags`
    GSL_LIBS=`${GSL_CONFIG} --libs`
else
    AC_MSG_ERROR([gsl-config not found, is GSL installed?])
fi

# Now substitute these variables in src/Makevars.in to create src/Makevars
AC_SUBST(GSL_CFLAGS)
AC_SUBST(GSL_LIBS)

AC_CONFIG_FILES([src/Makevars])
AC_OUTPUT
