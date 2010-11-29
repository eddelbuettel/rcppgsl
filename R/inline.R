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

inlineCxxPlugin <- Rcpp:::Rcpp.plugin.maker(
	include.before = "#include <RcppGSL.h>",
	#LinkingTo     = unique( c( package, "Rcpp", "RcppGSL" ) ),
	#Depends       = unique( c( package, "Rcpp", "RcppGSL" ) ),
	libs           = "-L/usr/lib -lgsl -lm $(LAPACK_LIBS) $(BLAS_LIBS) $(FLIBS)",
	package        = "RcppGSL"
)