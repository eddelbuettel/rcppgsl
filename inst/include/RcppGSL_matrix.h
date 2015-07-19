// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// RcppGSL_matrix.h: Rcpp/GSL glue
//
// Copyright (C)  2010 - 2015  Romain Francois and Dirk Eddelbuettel
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

namespace RcppGSL {

#undef _RCPPGSL_DEF
#define _RCPPGSL_DEF(__T__,__SUFFIX__)                                      \
inline void matrix<__T__>::import( SEXP x) throw(::Rcpp::not_compatible) {  \
	Rcpp::Matrix<RTYPE> mat( x );                                           \
	int nc = mat.ncol() ;                                                   \
	int nr = mat.nrow() ;                                                   \
	int i = 0, j = 0 ;                                                      \
	data = gsl_matrix##__SUFFIX__##_alloc( nr, nc ) ;                       \
	Rcpp::Matrix<RTYPE>::iterator it = mat.begin() ;                        \
	for( ; j<nc; j++){                                                      \
		for( i=0; i<nr; i++, it++){                                         \
			gsl_matrix##__SUFFIX__##_set( data, i, j, *it ) ;               \
		}                                                                   \
	}                                                                       \
}
#undef _RCPPGSL_DEF_CAST
#define _RCPPGSL_DEF_CAST(__T__,__SUFFIX__,__CAST__)                        \
inline void matrix<__T__>::import( SEXP x) throw(::Rcpp::not_compatible){   \
	Rcpp::Matrix<RTYPE> mat( x );                                           \
	int nc = mat.ncol() ;                                                   \
	int nr = mat.nrow() ;                                                   \
	int i = 0, j = 0 ;                                                      \
	data = gsl_matrix##__SUFFIX__##_alloc( nr, nc ) ;                       \
	Rcpp::Matrix<RTYPE>::iterator it = mat.begin() ;                        \
	typedef Rcpp::traits::storage_type<RTYPE>::type STORAGE ;               \
	for( ; j<nc; j++){                                                      \
		for( i=0; i<nr; i++, it++){                                         \
			gsl_matrix##__SUFFIX__##_set( data, i, j,                       \
				Rcpp::internal::caster<STORAGE,__CAST__>(*it) ) ;           \
		}                                                                   \
	}                                                                       \
}

inline void matrix<double>::import( SEXP x) throw(::Rcpp::not_compatible) {
	Rcpp::Matrix<RTYPE> mat( x );                                         
	int nc = mat.ncol() ;                                                 
	int nr = mat.nrow() ;                                                 
	int i = 0, j = 0 ;                                                    
	data = gsl_matrix_alloc( nr, nc ) ;                     
	Rcpp::Matrix<RTYPE>::iterator it = mat.begin() ;                      
	for( ; j<nc; j++){                                                    
		for( i=0; i<nr; i++, it++){                                       
			gsl_matrix_set( data, i, j, *it ) ;             
		}                                                                 
	}                                                                     
}

_RCPPGSL_DEF(int                      , _int   )
_RCPPGSL_DEF(unsigned char            , _uchar )

_RCPPGSL_DEF_CAST(float                    , _float                , float                   )
//_RCPPGSL_DEF_CAST(long                     , _long                 , long                    )
_RCPPGSL_DEF_CAST(long double              , _long_double          , long double             )
_RCPPGSL_DEF_CAST(short                    , _short                , short                   )
_RCPPGSL_DEF_CAST(unsigned int             , _uint                 , unsigned int            )
_RCPPGSL_DEF_CAST(unsigned short           , _ushort               , unsigned short          )
//_RCPPGSL_DEF_CAST(unsigned long            , _ulong                , unsigned long           )
_RCPPGSL_DEF_CAST(gsl_complex              , _complex              , gsl_complex             )
_RCPPGSL_DEF_CAST(gsl_complex_float        , _complex_float        , gsl_complex_float       )
_RCPPGSL_DEF_CAST(gsl_complex_long_double  , _complex_long_double  , gsl_complex_long_double )

inline void matrix<char>::import( SEXP x) throw(::Rcpp::not_compatible){
	Rcpp::Matrix<RAWSXP> mat( x );                                        
	int nc = mat.ncol() ;                                                
	int nr = mat.nrow() ;                                                
	int i = 0, j = 0 ;                                                   
	data = gsl_matrix_char_alloc( nr, nc ) ;                    
	Rcpp::Matrix<RAWSXP>::iterator it = mat.begin() ;                     
	for( ; j<nc; j++){                                                   
		for( i=0; i<nr; i++, it++){                                      
			gsl_matrix_char_set( data, i, j,                    
				static_cast<char>(*it) ) ;        
		}                                                                
	}                                                                    
}

#undef _RCPPGSL_DEF
#undef _RCPPGSL_DEF_CAST
	
}


namespace Rcpp{

template <typename T> SEXP wrap( const ::RcppGSL::matrix<T>& x){
	return wrap( *(x.data) ) ;
}

} 

#endif
