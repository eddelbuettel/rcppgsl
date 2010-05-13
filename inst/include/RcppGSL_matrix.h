// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
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

namespace RcppGSL {
	
	template <typename T> class gslmatrix_importer{
	public:
		typedef T r_import_type ; /* this is important */
		
	private:
		r_import_type* ptr ;
		int size1 ;
		int size2 ;
		int tda ;
		
	public:
		gslmatrix_importer( r_import_type* ptr_, int size1_, int size2_, int tda_ ) : 
			ptr(ptr_), size1(size1_), size2(size2_), tda(tda_){};
		inline int size() const { return size1 * size2 ; } ;
		r_import_type get( int i) const {
			int col = (int)( i / size1 ) ;
			int row = i - col * size1    ;
			return ptr[ row * tda + col ] ;
		}
	} ;               
}

namespace Rcpp{                                                                                  

#define RCPPGSL_WRAP(__TYPE__,__DATA__)                                  \
template <> SEXP wrap( const __TYPE__& x){                               \
	SEXP res = PROTECT( wrap( RcppGSL::gslmatrix_importer<__DATA__>(     \
		x.data, x.size1, x.size2, x.tda ) ) );	                           \
	SEXP dims = PROTECT( ::Rf_allocVector( INTSXP, 2) ) ;                \
	INTEGER(dims)[0] = x.size1 ;                                         \
	INTEGER(dims)[1] = x.size2 ;                                         \
	::Rf_setAttrib( res, R_DimSymbol, dims ) ;                           \
	UNPROTECT(2) ;                                                       \
	return res ;                                                         \
 }
#define RCPPGSL_WRAP_CAST(__TYPE__,__DATA__ )                            \
template <> SEXP wrap( const __TYPE__& x){                               \
	SEXP res = PROTECT( wrap( RcppGSL::gslmatrix_importer<__DATA__>(     \
		reinterpret_cast<__DATA__*>(x.data),                             \
		x.size1, x.size2, x.tda ) ) ) ;	                               \
	SEXP dims = PROTECT( ::Rf_allocVector( INTSXP, 2) ) ;                \
	INTEGER(dims)[0] = x.size1 ;                                         \
	INTEGER(dims)[1] = x.size2 ;                                         \
	::Rf_setAttrib( res, R_DimSymbol, dims ) ;                           \
	UNPROTECT(2) ;                                                       \
	return res ;                                                         \
}

RCPPGSL_WRAP(gsl_matrix             , double)
RCPPGSL_WRAP(gsl_matrix_float       , float)
RCPPGSL_WRAP(gsl_matrix_int         , int)
RCPPGSL_WRAP(gsl_matrix_long        , long)
RCPPGSL_WRAP(gsl_matrix_long_double , long double)
RCPPGSL_WRAP(gsl_matrix_short       , short)
RCPPGSL_WRAP(gsl_matrix_uchar       , unsigned char)
RCPPGSL_WRAP(gsl_matrix_uint        , unsigned int)
RCPPGSL_WRAP(gsl_matrix_ushort      , unsigned short)
RCPPGSL_WRAP(gsl_matrix_ulong       , unsigned long)

RCPPGSL_WRAP_CAST(gsl_matrix_char               ,Rbyte                   )
RCPPGSL_WRAP_CAST(gsl_matrix_complex            ,gsl_complex             )
RCPPGSL_WRAP_CAST(gsl_matrix_complex_float      ,gsl_complex_float       )
RCPPGSL_WRAP_CAST(gsl_matrix_complex_long_double,gsl_complex_long_double )

#undef RCPPGSL_WRAP
#undef RCPPGSL_WRAP_CAST

} 

#endif
