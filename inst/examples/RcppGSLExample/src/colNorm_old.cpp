
// colNorm.cpp: Rcpp and GSL based example of column norm
//              adapted from `Section 8.4.13 Example programs for matrices'
//              of the GSL manual
//
// Copyright (C)  2010 - 2026 Dirk Eddelbuettel and Romain Francois
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



// Just for completeness and history, this file contains some _older_
// versions of the column norm function. *You can ignore these.*
//
// Use the sibbling file colNorm.cpp as the reference implementation.



#include <RcppGSL.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

// old initial implementation, kept for comparison
extern "C" SEXP colNorm_old(SEXP sM) {

    try {

                RcppGSL::matrix<double> M = sM;         // create gsl data structures from SEXP
                int k = M.ncol();
                Rcpp::NumericVector n(k);               // to store results

                for (int j = 0; j < k; j++) {
                        RcppGSL::vector_view<double> colview = gsl_matrix_const_column (M, j);
                        n[j] = gsl_blas_dnrm2(colview);
                }
                M.free() ;
                return n;                               // return vector

    } catch( std::exception &ex ) {
                forward_exception_to_r( ex );

    } catch(...) {
                (Rf_error)("c++ exception (unknown reason)");
    }
    return R_NilValue; // -Wall
}


// newer Attributes-based implementation

// [[Rcpp::export]]
Rcpp::NumericVector colNorm_old2(Rcpp::NumericMatrix M) {
    // this conversion involves an allocation
    RcppGSL::matrix<double> G = Rcpp::as< RcppGSL::matrix<double> >(M);
    int k = G.ncol();
    Rcpp::NumericVector n(k);           // to store results
    for (int j = 0; j < k; j++) {
        RcppGSL::vector_view<double> colview = gsl_matrix_const_column (G, j);
        n[j] = gsl_blas_dnrm2(colview);
    }
    G.free();
    return n;                           // return vector
}

// newer Attributes-based simplementation with reference counting

// [[Rcpp::export]]
Rcpp::NumericVector colNorm_old3(RcppGSL::matrix<double> G) {
    int k = G.ncol();
    Rcpp::NumericVector n(k);           // to store results
    for (int j = 0; j < k; j++) {
        RcppGSL::vector_view<double> colview = gsl_matrix_column (G, j);
        n[j] = gsl_blas_dnrm2(colview);
    }
    return n;                           // return vector
}

