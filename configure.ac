
## Process this file with autoconf to produce a configure script.
##
## Configure.ac for RcppGSL
##
## Copyright (C) 2010 Romain Francois and Dirk Eddelbuettel
## Copyright (C) 2014 Dirk Eddelbuettel
##
## Licensed under GNU GPL 2 or later

# The version set here will propagate to other files from here
AC_INIT([RcppGSL], 0.2.0)

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

## Use Rscript to query Rcpp for compiler and linker flags
##
## look for Rscript, but use the one found via R_HOME to allow for multiple installations
dnl AC_DEFUN(AC_PROG_RSCRIPT, [AC_CHECK_PROG(RSCRIPT,Rscript,yes)])
dnl AC_PROG_RSCRIPT
dnl if test x"${RSCRIPT}" == x"yes" ; then
dnl      : ${R_HOME=`R RHOME`}
dnl      if test -z "${R_HOME}"; then
dnl          AC_MSG_ERROR([Could not determine R_HOME.])
dnl      fi
dnl      ## Rcpp compile flag providing header directory containing Rcpp.h
dnl      RCPP_CXXFLAGS=`${R_HOME}/bin/Rscript -e 'Rcpp:::CxxFlags()'`
dnl      ## link flag providing libary as well as path to library, and optionally rpath
dnl      RCPP_LDFLAGS=`${R_HOME}/bin/Rscript -e 'Rcpp:::LdFlags()'`
dnl else
dnl     AC_MSG_ERROR([Rscript not found, is R installed?])
dnl fi

# Now substitute these variables in src/Makevars.in to create src/Makevars
AC_SUBST(GSL_CFLAGS)
AC_SUBST(GSL_LIBS)
dnl AC_SUBST(RCPP_CXXFLAGS)
dnl AC_SUBST(RCPP_LDFLAGS)

AC_OUTPUT(src/Makevars)

