
// colNorm.cpp: Rcpp and GSL based example of column norm
//              adapted from `Section 8.4.13 Example programs for matrices' 
//              of the GSL manual
//
// Copyright (C)  2010 - 2020 Dirk Eddelbuettel and Romain Francois
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

// newest version using typedefs and const &
//
// see file colNorm_old.cpp for some older implementations if you are
// interested in comparing to those older versions, otherwise just enjoy
// this much shorter and simpler one

// [[Rcpp::export]]
Rcpp::NumericVector colNorm(const RcppGSL::Matrix & G) {
    int k = G.ncol();
    Rcpp::NumericVector n(k);           // to store results
    for (int j = 0; j < k; j++) {
        RcppGSL::VectorView colview = gsl_matrix_const_column (G, j);
        n[j] = gsl_blas_dnrm2(colview);
    }
    return n;                           // return vector
}



