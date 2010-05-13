// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// fastLm.cpp: Rcpp and GSL based implementation of lm
//
// Copyright (C)  2010 Dirk Eddelbuettel, Romain Francois
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


extern "C" SEXP fastLm(SEXP ys, SEXP Xs) {

    Rcpp::NumericVector Yr(ys);			// creates Rcpp vector from SEXP
    Rcpp::NumericMatrix Xr(Xs);			// creates Rcpp matrix from SEXP

    int i,j,n = Xr.nrow(), k = Xr.ncol();
    double chisq;

    gsl_matrix *X = gsl_matrix_alloc (n, k);
    gsl_vector *y = gsl_vector_alloc (n);
    gsl_vector *c = gsl_vector_alloc (k);
    gsl_matrix *cov = gsl_matrix_alloc (k, k);
    for (i = 0; i < n; i++) {
        for (j = 0; j < k; j++)
            gsl_matrix_set (X, i, j, Xr(i,j));
        gsl_vector_set (y, i, Yr(i));
    }

    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, k);
    gsl_multifit_linear (X, y, c, cov, &chisq, work);
    gsl_multifit_linear_free (work);


    //Rcpp::NumericVector coefr = Rcpp::wrap(c);
    RcppGSL::vector<double> coefr(5);
    RcppGSL::vector<double> vec(ys);
    //return Rcpp::List::create( Rcpp::Named( "coef", coefr),
    //                           Rcpp::Named( "stderr", coefr));
    return Xs;
}

