// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// RcppGSL.cpp: Rcpp/GSL glue
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

// helping the vignette
RCPP_FUNCTION_1( int, sum_gsl_vector_int, RcppGSL::vector<int> vec){
  int res = std::accumulate( vec.begin(), vec.end(), 0 ) ;
  vec.free() ;
  return res ;
}

RCPP_FUNCTION_1( double, gsl_vector_sum_2, Rcpp::List data ){
  // grab "x" as a gsl_vector through
  // the RcppGSL::vector<double> class
  RcppGSL::vector<double> x = data["x"] ;

  // grab "y" as a gsl_vector through
  // the RcppGSL::vector<int> class
  RcppGSL::vector<int> y = data["y"] ;
  double res = 0.0 ;
  for( size_t i=0; i< x->size; i++){
    res += x[i] * y[i] ;
  }

  // as usual with GSL, we need to explicitely free the
  // memory
  x.free() ;
  y.free() ;

  // return the result
  return res ;
}

