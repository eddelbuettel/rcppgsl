## Copyright (C) 2010 - 2012  Dirk Eddelbuettel and Romain Francois
## Copyright (C) 2014 - 2017  Dirk Eddelbuettel
##
## This file is part of RcppGSL.
##
## RcppGSL is free software: you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation, either version 2 of the License, or
## (at your option) any later version.
##
## RcppGSL is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with RcppGSL.  If not, see <http://www.gnu.org/licenses/>.

.pkgenv <- new.env(parent=emptyenv())

.onLoad <- function(libname, pkgname) {

    if (.Platform$OS.type=="windows") {
        LIB_GSL <- Sys.getenv("LIB_GSL")
        .pkgenv[["gsl_cflags"]] <- sprintf("-I%s/include", LIB_GSL)
        .pkgenv[["gsl_libs"]]   <- sprintf("-L%s/lib -lgsl -lgslcblas", LIB_GSL)
    } else {
        if (unname(Sys.which("gsl-config")) != "") {
            .pkgenv[["gsl_cflags"]] <- system("gsl-config --cflags", intern = TRUE)
            .pkgenv[["gsl_libs"]]   <- system("gsl-config --libs"  , intern = TRUE)
        } else {
            .pkgenv[["gsl_cflags"]] <- ""
            .pkgenv[["gsl_libs"]]   <- ""
            warning("No 'gsl-config' config script found, limiting extensibility.", call. = FALSE)
        }
    }
}

LdFlags <- function(print = TRUE) {
    if (print) cat(.pkgenv$gsl_libs) else .pkgenv$gsl_libs
}

CFlags <- function(print = TRUE) {
    if (print) cat(.pkgenv$gsl_cflags) else .pkgenv$gsl_cflags
}

inlineCxxPlugin <- function(...) {
    plugin <- Rcpp::Rcpp.plugin.maker(
        include.before = "#include <RcppGSL.h>",
        libs = sprintf( "%s $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)", LdFlags(FALSE)),
        package = "RcppGSL", Makevars = NULL, Makevars.win = NULL
    )
    settings <- plugin()
    settings$env$PKG_CPPFLAGS <- CFlags(FALSE)
    settings$configure <- readLines(system.file("skeleton", "configure", package="RcppGSL"))
    settings$configure.win <- readLines(system.file("skeleton", "configure.win", package="RcppGSL"))
    settings$Makevars.in <- readLines(system.file("skeleton", "Makevars.in", package = "RcppGSL"))
    settings
}


