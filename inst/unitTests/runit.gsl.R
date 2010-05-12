#!/usr/bin/r -t
#
# Copyright (C) 2010	Romain Francois and Dirk Eddelbuettel
#
# This file is part of RcppGSL.
#
# RcppGSL is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# RcppGSL is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RcppGSL.  If not, see <http://www.gnu.org/licenses/>.

test.gsl.vector.wrappers <- function(){
	res <- .Call( "test_gsl_vector_wrapper", PACKAGE = "RcppGSL" )
	checkEquals( res, 
		list( 
			"gsl_vector" = numeric(10), 
			"gsl_vector_float" = numeric(10), 
			"gsl_vector_int" = integer(10), 
			"gsl_vector_long" = numeric(10), 
			"gsl_vector_char" = raw(10), 
			"gsl_vector_complex" = complex(10), 
			"gsl_vector_complex_float" = complex(10), 
			"gsl_vector_complex_long_double" = complex(10), 
			"gsl_vector_long_double" = numeric(10), 
			"gsl_vector_short" = integer(10), 
			"gsl_vector_uchar" = raw(10), 
			"gsl_vector_uint" = integer(10), 
			"gsl_vector_ushort" = integer(10), 
			"gsl_vector_ulong" = numeric(10)
		), 
		msg = "wrap( gsl_vector )" )
}

test.gsl.vector <- function(){
	res <- .Call( "test_gsl_vector", PACKAGE = "RcppGSL" )
	checkEquals( res, 
		list( 
			"gsl_vector" = numeric(10), 
			"gsl_vector_float" = numeric(10), 
			"gsl_vector_int" = integer(10), 
			"gsl_vector_long" = numeric(10), 
			"gsl_vector_char" = raw(10), 
			"gsl_vector_complex" = complex(10), 
			"gsl_vector_complex_float" = complex(10), 
			"gsl_vector_complex_long_double" = complex(10), 
			"gsl_vector_long_double" = numeric(10), 
			"gsl_vector_short" = integer(10), 
			"gsl_vector_uchar" = raw(10), 
			"gsl_vector_uint" = integer(10), 
			"gsl_vector_ushort" = integer(10), 
			"gsl_vector_ulong" = numeric(10)
		), 
		msg = "wrap( gsl_vector )" )
}

test.gsl.matrix <- function(){
	helper <- function(what){
		as.what <- get( paste( "as.", deparse(substitute(what)), sep = "" ) )
		x <- what(10)
		x[1] <- as.what(1) 
		x[7] <- as.what(1)
		dim( x )  <- c(5,2)
		x
	}
	res <- .Call( "test_gsl_matrix", PACKAGE = "RcppGSL" )
	checkEquals( res, 
		list( 
			"gsl_matrix"                     = helper( numeric ), 
			"gsl_matrix_float"               = helper( numeric ), 
			"gsl_matrix_int"                 = helper( integer ), 
			"gsl_matrix_long"                = helper( numeric ), 
			"gsl_matrix_char"                = helper( raw ), 
			"gsl_matrix_complex"             = helper( complex ), 
			"gsl_matrix_complex_float"       = helper( complex ), 
			"gsl_matrix_complex_long_double" = helper( complex ), 
			"gsl_matrix_long_double"         = helper( numeric ), 
			"gsl_matrix_short"               = helper( integer ), 
			"gsl_matrix_uchar"               = helper( raw ), 
			"gsl_matrix_uint"                = helper( integer ), 
			"gsl_matrix_ushort"              = helper( integer ), 
			"gsl_matrix_ulong"               = helper( numeric )
		), 
		msg = "wrap( gsl_matrix )" )

}

test.gsl.vector.view <- function(){
	res <- .Call( "test_gsl_vector_view", PACKAGE = "RcppGSL" )
	checkEquals( res, 
		list( even = 2.0 * 0:4, odd = 2.0 * 0:4 + 1.0 ), 
		msg = "wrap( gsl.vector.view )" )
}

test.gsl.matrix.view <- function(){
	res <- .Call( "test_gsl_matrix_view", PACKAGE = "RcppGSL" )
	checkEquals( res$full[3:4, 3:4], res$view, msg = "wrap(gsl.matrix.view)" )
}
      
test.gsl.vector.input.SEXP <- function(){
	x <- rnorm( 10 )
	res <- .Call( "test_gsl_vector_input", x, PACKAGE = "RcppGSL" )
	checkEquals( res, sum(x), msg = "RcppGSL::vector<double>(SEXP)" )
}

