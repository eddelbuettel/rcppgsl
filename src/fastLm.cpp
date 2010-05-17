// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// fastLm.cpp: Rcpp and GSL based implementation of lm
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

#include <gsl/gsl_multifit.h>
#include <cmath>

extern "C" SEXP fastLm(SEXP ys, SEXP Xs) {

    try {
	
		RcppGSL::vector<double> y = ys;		// create gsl data structures from SEXP
		RcppGSL::matrix<double> X = Xs; 
	
		int n = X.nrow(), k = X.ncol();
		double chisq;

		RcppGSL::vector<double> coef(k); 	// to hold the coefficient vector 
		RcppGSL::matrix<double> cov(k,k);	// and the covariance matrix
    
		// the actual fit requires working memory we allocate and free
		gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, k);
		gsl_multifit_linear (X, y, coef, cov, &chisq, work);
		gsl_multifit_linear_free (work);
     
		// extract the diagonal as a vector view
		gsl_vector_view diag = gsl_matrix_diagonal(cov) ;
          
		// currently there is not a more direct interface in Rcpp::NumericVector
		// that takes advantage of wrap, so we have to do it in two steps
		Rcpp::NumericVector stderr ; stderr = diag;
		std::transform( stderr.begin(), stderr.end(), stderr.begin(), sqrt );

		Rcpp::List res = Rcpp::List::create(Rcpp::Named("coefficients") = coef, 
											Rcpp::Named("stderr") = stderr,
											Rcpp::Named("df") = n - k);

		// free all the GSL vectors and matrices -- as these are really C data structure
		// we cannot take advantage of automatic memory management
		coef.free() ;
		cov.free();
		y.free();
		X.free();

		return res;    // return the result list to R 
	    
    } catch( std::exception &ex ) {
		forward_exception_to_r( ex );

    } catch(...) { 
		::Rf_error( "c++ exception (unknown reason)" ); 
    }
    
}

