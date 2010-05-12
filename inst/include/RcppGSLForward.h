// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// RcppGSLForward.h: Rcpp/GSL glue
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

#ifndef RCPPGSL__RCPPGSLFORWARD_H
#define RCPPGSL__RCPPGSLFORWARD_H

#include <RcppCommon.h>
#include <gsl/gsl_vector.h> 
#include <gsl/gsl_matrix.h>

namespace Rcpp{

	namespace traits{
		/* support for gsl_complex */
		template<> struct r_sexptype_traits<gsl_complex>{ enum{ rtype = CPLXSXP } ; } ;
		template<> struct wrap_type_traits<gsl_complex> { typedef wrap_type_primitive_tag wrap_category; } ;
		template<> struct r_type_traits<gsl_complex>{ typedef r_type_primitive_tag r_category ; } ;
		template<> struct r_type_traits< std::pair<const std::string,gsl_complex> >{ typedef r_type_primitive_tag r_category ; } ;
	
		/* support for gsl_complex_float */
		template<> struct r_sexptype_traits<gsl_complex_float>{ enum{ rtype = CPLXSXP } ; } ;
		template<> struct wrap_type_traits<gsl_complex_float> { typedef wrap_type_primitive_tag wrap_category; } ;
		template<> struct r_type_traits<gsl_complex_float>{ typedef r_type_primitive_tag r_category ; } ;
		template<> struct r_type_traits< std::pair<const std::string,gsl_complex_float> >{ typedef r_type_primitive_tag r_category ; } ;
	
		/* support for gsl_complex_long_double */
		template<> struct r_sexptype_traits<gsl_complex_long_double>{ enum{ rtype = CPLXSXP } ; } ;
		template<> struct wrap_type_traits<gsl_complex_long_double> { typedef wrap_type_primitive_tag wrap_category; } ;
		template<> struct r_type_traits<gsl_complex_long_double>{ typedef r_type_primitive_tag r_category ; } ;
		template<> struct r_type_traits< std::pair<const std::string,gsl_complex_long_double> >{ typedef r_type_primitive_tag r_category ; } ;
	
	}
	
	namespace internal{
		template<> gsl_complex caster<Rcomplex,gsl_complex>( Rcomplex from) ;
		template<> Rcomplex caster<gsl_complex,Rcomplex>( gsl_complex from) ;
		
		template<> gsl_complex_float caster<Rcomplex,gsl_complex_float>( Rcomplex from) ;
		template<> Rcomplex caster<gsl_complex_float,Rcomplex>( gsl_complex_float from) ;
    
		template<> gsl_complex_long_double caster<Rcomplex,gsl_complex_long_double>( Rcomplex from) ;
		template<> Rcomplex caster<gsl_complex_long_double,Rcomplex>( gsl_complex_long_double from) ;
    }

}

namespace RcppGSL{
	template <typename T> class vector ;
	template <typename T> class vector_view ;
	
#undef _RCPPGSL_SPEC
#define _RCPPGSL_SPEC(__T__,__SUFFIX__,__CAST__)      	                        \
template <> class vector<__T__>  {           	                                   \
public:                                      	                                   \
	typedef __T__ type ;                     	                                   \
	typedef __T__* pointer ;                 	                                   \
	typedef gsl_vector##__SUFFIX__ gsltype ; 	                                   \
	gsltype* data ;                          	                                   \
	const static int RTYPE = ::Rcpp::traits::r_sexptype_traits<type>::rtype ;    \
	vector( SEXP x) throw(::Rcpp::not_compatible) : data(0) {                    \
		SEXP y = ::Rcpp::r_cast<RTYPE>(x) ;                                      \
		int size = ::Rf_length( y ) ;                                            \
		data = gsl_vector##__SUFFIX__##_calloc( size ) ;                         \
		::Rcpp::internal::export_range<__CAST__*>( y,                            \
			reinterpret_cast<__CAST__*>( data->data ) ) ;                        \
	}                                                                            \
	vector( gsltype* x) : data(x) {}                                             \
	vector( int size) :                                                          \
		data( gsl_vector##__SUFFIX__##_calloc( size ) ){}                        \
	~vector(){ }                                                                 \
	operator gsltype*(){ return data ; }                                         \
	gsltype* operator->() const { return data; }                                 \
	gsltype& operator*() const { return *data; }                                 \
	vector( const vector& x) : data(x.data)  {}                                  \
	vector& operator=(const vector& other) {                                     \
		data = other.data ;                                                      \
		return *this ;                                                           \
	}                                                                            \
	void free(){                                                                 \
		gsl_vector##__SUFFIX__##_free(data) ;                                    \
	}                                                                            \
} ;                                                                              \
template <> class vector_view<__T__>  {           	                            \
public:                                      	                                   \
	typedef __T__ type ;                     	                                   \
	typedef __T__* pointer ;                 	                                   \
	typedef gsl_vector##__SUFFIX__##_view gsltype ; 	                           \
	gsltype* data ;                          	                                   \
	vector_view( gsltype* x) : data(x) {}                                        \
	~vector_view(){  }                                                           \
	operator gsltype*(){ return data ; }                                         \
	gsltype* operator->() const { return data; }                                 \
	gsltype& operator*() const { return *data; }                                 \
	vector_view( const vector_view& x) : data(x.data)  {}                        \
	vector_view& operator=(const vector_view& other) {                           \
		data = other.data ;                                                      \
		return *this ;                                                           \
	}                                                                            \
} ;                                                                             \

// template <> class matrix<__T__>  {           	                                   \     
// public:                                      	                                   \     
// 	typedef __T__ type ;                     	                                   \     
// 	typedef __T__* pointer ;                 	                                   \     
// 	typedef gsl_matrix##__SUFFIX__ gsltype ; 	                                   \     
// 	gsltype* data ;                          	                                   \     
// 	const static int RTYPE = ::Rcpp::traits::r_sexptype_traits<type>::rtype ;    \       
// 	matrix( SEXP x) throw(::Rcpp::not_compatible) : data(0) {                    \       
// 		if( !Rf_isMatrix(x) ) throw not_compatible("not a matrix") ;             \       
// 		SEXP y = ::Rcpp::internal::rowmajor_wrap( ) ;                            \       
// 		data = gsl_matrix##__SUFFIX__##_calloc( size ) ;                         \       
// 		::Rcpp::internal::export_range<__CAST__*>( y,                            \       
// 			reinterpret_cast<__CAST__*>( data->data ) ) ;                        \       
// 	}                                                                            \       
// 	matrix( gsltype* x) : data(x) {}                                             \       
// 	matrix( int nrow, int ncol) :                                                \       
// 		data( gsl_matrix##__SUFFIX__##_alloc( nrow, ncol ) ){}                   \       
// 	~matrix(){ }                                                                 \       
// 	operator gsltype*(){ return data ; }                                         \       
// 	gsltype* operator->() const { return data; }                                 \       
// 	gsltype& operator*() const { return *data; }                                 \       
// 	matrix( const matrix& x) : data(x.data)  {}                                  \       
// 	matrix& operator=(const matrix& other) {                                     \       
// 		data = other.data ;                                                      \       
// 		return *this ;                                                           \       
// 	}                                                                            \       
// 	void free(){                                                                 \       
// 		gsl_matrix##__SUFFIX__##_free(data) ;                                    \       
// 	}                                                                            \       
// } ;                                                                              \       
//  


_RCPPGSL_SPEC(double                   ,                       , double                  )
_RCPPGSL_SPEC(float                    , _float                , float                   )
_RCPPGSL_SPEC(int                      , _int                  , int                     )
_RCPPGSL_SPEC(long                     , _long                 , long                    )
_RCPPGSL_SPEC(long double              , _long_double          , long double             )
_RCPPGSL_SPEC(short                    , _short                , short                   )
_RCPPGSL_SPEC(unsigned char            , _uchar                , unsigned char           )
_RCPPGSL_SPEC(unsigned int             , _uint                 , unsigned int            )
_RCPPGSL_SPEC(unsigned short           , _ushort               , unsigned short          )
_RCPPGSL_SPEC(unsigned long            , _ulong                , unsigned long           )
_RCPPGSL_SPEC(char                     , _char                 , unsigned char           )
_RCPPGSL_SPEC(gsl_complex              , _complex              , gsl_complex             )
_RCPPGSL_SPEC(gsl_complex_float        , _complex_float        , gsl_complex_float       )
_RCPPGSL_SPEC(gsl_complex_long_double  , _complex_long_double  , gsl_complex_long_double )

#undef _RCPPGSL_SPEC
 
}


/* forward declarations */
namespace Rcpp{

	template <> SEXP wrap( const gsl_vector& ) ;
	template <> SEXP wrap( const gsl_vector_int& ) ;
	template <> SEXP wrap( const gsl_vector_float& ) ;
	template <> SEXP wrap( const gsl_vector_long& ) ;
	template <> SEXP wrap( const gsl_vector_char& ) ;
	template <> SEXP wrap( const gsl_vector_complex& ) ;
	template <> SEXP wrap( const gsl_vector_complex_float& ) ;
	template <> SEXP wrap( const gsl_vector_complex_long_double& ) ;
	template <> SEXP wrap( const gsl_vector_long_double& ) ;
	template <> SEXP wrap( const gsl_vector_short& ) ;
	template <> SEXP wrap( const gsl_vector_uchar& ) ;
	template <> SEXP wrap( const gsl_vector_uint& ) ;
	template <> SEXP wrap( const gsl_vector_ushort& ) ;
	template <> SEXP wrap( const gsl_vector_ulong& ) ;
	
	template <> SEXP wrap( const gsl_vector_view& ) ;
	template <> SEXP wrap( const gsl_vector_int_view& ) ;
	template <> SEXP wrap( const gsl_vector_float_view& ) ;
	template <> SEXP wrap( const gsl_vector_long_view& ) ;
	template <> SEXP wrap( const gsl_vector_char_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_float_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_long_double_view& ) ;
	template <> SEXP wrap( const gsl_vector_long_double_view& ) ;
	template <> SEXP wrap( const gsl_vector_short_view& ) ;
	template <> SEXP wrap( const gsl_vector_uchar_view& ) ;
	template <> SEXP wrap( const gsl_vector_uint_view& ) ;
	template <> SEXP wrap( const gsl_vector_ushort_view& ) ;
	template <> SEXP wrap( const gsl_vector_ulong_view& ) ;
	
	template <> SEXP wrap( const gsl_vector_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_int_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_float_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_long_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_char_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_float_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_complex_long_double_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_long_double_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_short_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_uchar_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_uint_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_ushort_const_view& ) ;
	template <> SEXP wrap( const gsl_vector_ulong_const_view& ) ;

	
	template <> SEXP wrap( const gsl_matrix& ) ;
	template <> SEXP wrap( const gsl_matrix_int& ) ;
	template <> SEXP wrap( const gsl_matrix_float& ) ;
	template <> SEXP wrap( const gsl_matrix_long& ) ;
	template <> SEXP wrap( const gsl_matrix_char& ) ;
	template <> SEXP wrap( const gsl_matrix_complex& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_float& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_long_double& ) ;
	template <> SEXP wrap( const gsl_matrix_long_double& ) ;
	template <> SEXP wrap( const gsl_matrix_short& ) ;
	template <> SEXP wrap( const gsl_matrix_uchar& ) ;
	template <> SEXP wrap( const gsl_matrix_uint& ) ;
	template <> SEXP wrap( const gsl_matrix_ushort& ) ;
	template <> SEXP wrap( const gsl_matrix_ulong& ) ;
	
	template <> SEXP wrap( const gsl_matrix_view& ) ;
	template <> SEXP wrap( const gsl_matrix_int_view& ) ;
	template <> SEXP wrap( const gsl_matrix_float_view& ) ;
	template <> SEXP wrap( const gsl_matrix_long_view& ) ;
	template <> SEXP wrap( const gsl_matrix_char_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_float_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_long_double_view& ) ;
	template <> SEXP wrap( const gsl_matrix_long_double_view& ) ;
	template <> SEXP wrap( const gsl_matrix_short_view& ) ;
	template <> SEXP wrap( const gsl_matrix_uchar_view& ) ;
	template <> SEXP wrap( const gsl_matrix_uint_view& ) ;
	template <> SEXP wrap( const gsl_matrix_ushort_view& ) ;
	template <> SEXP wrap( const gsl_matrix_ulong_view& ) ;
	
	template <> SEXP wrap( const gsl_matrix_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_int_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_float_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_long_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_char_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_float_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_complex_long_double_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_long_double_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_short_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_uchar_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_uint_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_ushort_const_view& ) ;
	template <> SEXP wrap( const gsl_matrix_ulong_const_view& ) ;

	template <typename T> SEXP wrap( const ::RcppGSL::vector<T>& ) ;
	template <typename T> SEXP wrap( const ::RcppGSL::vector_view<T>& ) ;
	 
}

#endif
