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
	
		template<> inline gsl_complex caster<Rcomplex,gsl_complex>( Rcomplex from){
			gsl_complex x ;
			GSL_REAL(x) = from.r ;
			GSL_IMAG(x) = from.i ;
			return x ;
		}
		template<> inline Rcomplex caster<gsl_complex,Rcomplex>( gsl_complex from){
			Rcomplex x ;
			x.r = GSL_REAL(from) ;
			x.i = GSL_IMAG(from) ;
			return x ;
		}
		
		template<> inline gsl_complex_float caster<Rcomplex,gsl_complex_float>( Rcomplex from){
			gsl_complex_float x ;
			GSL_REAL(x) = static_cast<float>( from.r ) ;
			GSL_IMAG(x) = static_cast<float>( from.i ) ;
			return x ;
		}
		template<> inline Rcomplex caster<gsl_complex_float,Rcomplex>( gsl_complex_float from){
			Rcomplex x ;
			x.r = static_cast<double>( GSL_REAL(from) ) ;
			x.i = static_cast<double>( GSL_IMAG(from) ) ;
			return x ;
		}
	
		template<> inline gsl_complex_long_double caster<Rcomplex,gsl_complex_long_double>( Rcomplex from){
			gsl_complex_long_double x ;
			GSL_REAL(x) = static_cast<float>( from.r ) ;
			GSL_IMAG(x) = static_cast<float>( from.i ) ;
			return x ;
		}
		template<> inline Rcomplex caster<gsl_complex_long_double,Rcomplex>( gsl_complex_long_double from){
			Rcomplex x ;
			x.r = static_cast<double>( GSL_REAL(from) ) ;
			x.i = static_cast<double>( GSL_IMAG(from) ) ;
			return x ;
		}
	}

}

namespace RcppGSL{
	template <typename T> class vector ;
	template <typename T> class matrix ;
	
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
	inline size_t size(){ return data->size ; }                                  \
	void free(){                                                                 \
		gsl_vector##__SUFFIX__##_free(data) ;                                    \
	}                                                                            \
} ;                                                                              \
template <> class matrix<__T__>  {           	                                   \
public:                                      	                                   \
	typedef __T__ type ;                     	                                   \
	typedef __T__* pointer ;                 	                                   \
	typedef gsl_matrix##__SUFFIX__ gsltype ; 	                                   \
	gsltype* data ;                          	                                   \
	const static int RTYPE = ::Rcpp::traits::r_sexptype_traits<type>::rtype ;    \
	matrix( SEXP x) throw(::Rcpp::not_compatible) : data(0) { import(x); }       \
	matrix( gsltype* x) : data(x) {}                                             \
	matrix( int nrow, int ncol) :                                                \
		data( gsl_matrix##__SUFFIX__##_alloc( nrow, ncol ) ){}                   \
	~matrix(){ }                                                                 \
	operator gsltype*(){ return data ; }                                         \
	gsltype* operator->() const { return data; }                                 \
	gsltype& operator*() const { return *data; }                                 \
	matrix( const matrix& x) : data(x.data)  {}                                  \
	matrix& operator=(const matrix& other) {                                     \
		data = other.data ;                                                      \
		return *this ;                                                           \
	}                                                                            \
	inline size_t nrow(){ return data->size1 ; }                                 \
	inline size_t ncol(){ return data->size2 ; }                                 \
	inline size_t size(){ return data->size1 * data->size2 ; }                   \
	void free(){                                                                 \
		gsl_matrix##__SUFFIX__##_free(data) ;                                    \
	}                                                                            \
private:                                                                         \
	inline void import(SEXP x) throw(::Rcpp::not_compatible);                    \
} ;                                                                              \

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

#undef _RCPPGSL_WRAPDEF
#define _RCPPGSL_WRAPDEF(__SUFFIX__)                                          \
template<> inline SEXP wrap( const gsl_vector##__SUFFIX__& ) ;                \
template<> inline SEXP wrap( const gsl_vector##__SUFFIX__##_view& ) ;         \
template<> inline SEXP wrap( const gsl_vector##__SUFFIX__##_const_view& ) ;   \
template<> inline SEXP wrap( const gsl_matrix##__SUFFIX__& ) ;                \
template<> inline SEXP wrap( const gsl_matrix##__SUFFIX__##_view& ) ;         \
template<> inline SEXP wrap( const gsl_matrix##__SUFFIX__##_const_view& ) ;

_RCPPGSL_WRAPDEF()
_RCPPGSL_WRAPDEF(_int ) 
_RCPPGSL_WRAPDEF(_float ) 
_RCPPGSL_WRAPDEF(_long ) 
_RCPPGSL_WRAPDEF(_char ) 
_RCPPGSL_WRAPDEF(_complex ) 
_RCPPGSL_WRAPDEF(_complex_float ) 
_RCPPGSL_WRAPDEF(_complex_long_double ) 
_RCPPGSL_WRAPDEF(_long_double ) 
_RCPPGSL_WRAPDEF(_short ) 
_RCPPGSL_WRAPDEF(_uchar ) 
_RCPPGSL_WRAPDEF(_uint ) 
_RCPPGSL_WRAPDEF(_ushort ) 
_RCPPGSL_WRAPDEF(_ulong ) 

	template <typename T> SEXP wrap( const ::RcppGSL::vector<T>& ) ;
	template <typename T> SEXP wrap( const ::RcppGSL::matrix<T>& ) ;
	 
}

#endif
