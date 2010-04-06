// RcppGSL_matrix.h: Rcpp/GSL glue
//
// Copyright (C)  2010 Romain Francois and Dirk Eddelbuettel
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

#ifndef RCPPGSL__RCPPGSL_MATRIX_H
#define RCPPGSL__RCPPGSL_MATRIX_H

#include <RcppGSLForward.h>
#include <Rcpp.h>
#include <RcppGSL_caster.h> 

namespace Rcpp{

template <> SEXP wrap( const gsl_matrix& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_float& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_int& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_long& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_char& x){
	return internal::rowmajor_wrap( reinterpret_cast<Rbyte*>(x.data), x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_complex& x){
	return internal::rowmajor_wrap( reinterpret_cast<gsl_complex*>(x.data), x.size1, x.size2 ) ;
}
 
template <> SEXP wrap( const gsl_matrix_complex_float& x){
	return internal::rowmajor_wrap( reinterpret_cast<gsl_complex_float*>(x.data), x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_complex_long_double& x){
	return internal::rowmajor_wrap( reinterpret_cast<gsl_complex_long_double*>(x.data), x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_long_double& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_short& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_uchar& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_uint& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_ushort& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

template <> SEXP wrap( const gsl_matrix_ulong& x){
	return internal::rowmajor_wrap( x.data, x.size1, x.size2 ) ;
}

} 

#endif
