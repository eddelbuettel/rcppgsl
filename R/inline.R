## Copyright (C)       2010 Dirk Eddelbuettel and Romain Francois
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
## along with RcppArmadillo.  If not, see <http://www.gnu.org/licenses/>.

NAMESPACE <- environment()

if(.Platform$OS.type=="windows") {
    LIB_GSL <- Sys.getenv("LIB_GSL")
    gsl_cflags <- sprintf( "-I%s/include", LIB_GSL )
    gsl_libs   <- sprintf( "-L%s/lib -lgsl -lgslcblas", LIB_GSL )
    know_flags <- TRUE
} else {             
    gsl_cflags <- ""
    gsl_libs <- ""
    know_flags <- FALSE    
}

get_gsl_flags <- function(){
    td <- tempfile()
    here <- getwd()
    dir.create( td ); on.exit( {
        setwd( here )         
        unlink( td, recursive = TRUE )
    } )
    
    file.copy( 
        system.file( "detective", "configure.in", package = "RcppGSL" ), 
        td )
    file.copy( 
        system.file( "detective", "Makevars.in", package = "RcppGSL" ), 
        td )
    setwd( td )
    
    system( "autoconf" )
    system( "sh configure" )
    
    txt <- readLines( "Makevars" )
    gsl_cflags <- sub( "^GSL_CFLAGS[[:space:]]*=[[:space:]]*", "" , grep( "^GSL_CFLAGS", txt, value = TRUE ) )
    gsl_libs   <- sub( "^GSL_LIBS[[:space:]]*=[[:space:]]*", "" , grep( "^GSL_LIBS", txt, value = TRUE ) )
    
    unlockBinding( "gsl_cflags", NAMESPACE )
    unlockBinding( "gsl_libs", NAMESPACE )
    unlockBinding( "know_flags", NAMESPACE )
    
    assign( "gsl_cflags", gsl_cflags, NAMESPACE )
    assign( "gsl_libs", gsl_libs, NAMESPACE )
    assign( "know_flags", TRUE, NAMESPACE )
    
    lockBinding( "gsl_cflags", NAMESPACE )
    lockBinding( "gsl_libs", NAMESPACE )
    lockBinding( "know_flags", NAMESPACE )
       
}
       

LdFlags <- function(){
    if( ! know_flags ) {
        get_gsl_flags()
    }
    gsl_libs
}

CFlags <- function(){
    if( ! know_flags ) {
        get_gsl_flags()
    }
    gsl_cflags
}

inlineCxxPlugin <- function(...) {
    plugin <- Rcpp:::Rcpp.plugin.maker(
        include.before = "#include <RcppGSL.h>",
        libs = sprintf( "%s $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)", LdFlags() ),
        package = "RcppGSL"
    )
    settings <- plugin()
    settings$env$PKG_CPPFLAGS <- CFlags()
    settings
}


