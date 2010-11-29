// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// colNorm.cpp: Rcpp and GSL based example of column norm
//              adapted from `Section 8.4.13 Example programs for matrices' 
//              of the GSL manual
//
// Copyright (C)  2010 Dirk Eddelbuettel and Romain Francois
//
// This file is part of RcppGSL.
//
// RcppGSL is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// RcppGSL is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with RcppGSL.  If not, see <http://www.gnu.org/licenses/>.


#include <RcppGSL.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

extern "C" SEXP colNorm(SEXP sM) {

    try {
		
		RcppGSL::matrix<double> M = sM; 	// create gsl data structures from SEXP
		int k = M.ncol();
		Rcpp::NumericVector n(k); 			// to store results 

		for (int j = 0; j < k; j++) {
			RcppGSL::vector_view<double> colview = gsl_matrix_column (M, j);
			n[j] = gsl_blas_dnrm2(colview.vector_ );
		}
		M.free() ;
		return n;							// return vector  

    } catch( std::exception &ex ) {
		forward_exception_to_r( ex );

    } catch(...) { 
		::Rf_error( "c++ exception (unknown reason)" ); 
    }
    return R_NilValue; // -Wall
}

