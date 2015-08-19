// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// RcppGSLForward.h: Forward Declarations for Seamless R and GSL Integration
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

#ifndef RCPPGSL__RCPPGSLFORWARD_H
#define RCPPGSL__RCPPGSLFORWARD_H

#include <RcppCommon.h>
#include <gsl/gsl_vector.h> 
#include <gsl/gsl_matrix.h>

namespace Rcpp {

    namespace traits {
        /* support for gsl_complex */
        template<> struct r_sexptype_traits<gsl_complex> { enum { rtype = CPLXSXP }; };
        template<> struct wrap_type_traits<gsl_complex> { typedef wrap_type_primitive_tag wrap_category; };
        template<> struct r_type_traits<gsl_complex> { typedef r_type_primitive_tag r_category; };
        template<> struct r_type_traits< std::pair<const std::string, gsl_complex> > { typedef r_type_primitive_tag r_category; };
    
        /* support for gsl_complex_float */
        template<> struct r_sexptype_traits<gsl_complex_float> { enum { rtype = CPLXSXP }; };
        template<> struct wrap_type_traits<gsl_complex_float> { typedef wrap_type_primitive_tag wrap_category; };
        template<> struct r_type_traits<gsl_complex_float> { typedef r_type_primitive_tag r_category; };
        template<> struct r_type_traits< std::pair<const std::string, gsl_complex_float> > { typedef r_type_primitive_tag r_category; };
    
        /* support for gsl_complex_long_double */
        template<> struct r_sexptype_traits<gsl_complex_long_double> { enum { rtype = CPLXSXP }; };
        template<> struct wrap_type_traits<gsl_complex_long_double> { typedef wrap_type_primitive_tag wrap_category; };
        template<> struct r_type_traits<gsl_complex_long_double> { typedef r_type_primitive_tag r_category; };
        template<> struct r_type_traits< std::pair<const std::string, gsl_complex_long_double> > { typedef r_type_primitive_tag r_category; };
    
    }
    
    namespace internal {
    
        template<> inline gsl_complex caster<Rcomplex,gsl_complex>(Rcomplex from) {
            gsl_complex x;
            GSL_REAL(x) = from.r;
            GSL_IMAG(x) = from.i;
            return x;
        }
       
        template<> inline Rcomplex caster<gsl_complex,Rcomplex>(gsl_complex from) {
            Rcomplex x;
            x.r = GSL_REAL(from);
            x.i = GSL_IMAG(from);
            return x;
        }
        
        template<> inline gsl_complex_float caster<Rcomplex,gsl_complex_float>(Rcomplex from) {
            gsl_complex_float x;
            GSL_REAL(x) = static_cast<float>(from.r);
            GSL_IMAG(x) = static_cast<float>(from.i);
            return x;
        }
        
        template<> inline Rcomplex caster<gsl_complex_float,Rcomplex>(gsl_complex_float from) {
            Rcomplex x;
            x.r = static_cast<double>(GSL_REAL(from));
            x.i = static_cast<double>(GSL_IMAG(from));
            return x;
        }
    
        template<> inline gsl_complex_long_double caster<Rcomplex,gsl_complex_long_double>(Rcomplex from) {
            gsl_complex_long_double x;
            GSL_REAL(x) = static_cast<float>(from.r);
            GSL_IMAG(x) = static_cast<float>(from.i);
            return x;
        }
        
        template<> inline Rcomplex caster<gsl_complex_long_double,Rcomplex>(gsl_complex_long_double from) {
            Rcomplex x;
            x.r = static_cast<double>(GSL_REAL(from));
            x.i = static_cast<double>(GSL_IMAG(from));
            return x;
        }
    }
}

namespace RcppGSL {
    template <typename T> class vector;
    template <typename T> class matrix;
    template <typename T> struct vector_view_type;
    template <typename T> struct matrix_view_type;
    
    #include "RcppGSL_types.h"

    _RCPPGSL_SPEC_NOSUFFIX(double          , double                                         )
    _RCPPGSL_SPEC(float                    , _float                , float                  )
    _RCPPGSL_SPEC(int                      , _int                  , int                    )
    //_RCPPGSL_SPEC(long                   , _long                 , long                   )
    _RCPPGSL_SPEC(long double              , _long_double          , long double            )
    _RCPPGSL_SPEC(short                    , _short                , short                  )
    _RCPPGSL_SPEC(unsigned char            , _uchar                , unsigned char          )
    _RCPPGSL_SPEC(unsigned int             , _uint                 , unsigned int           )
    _RCPPGSL_SPEC(unsigned short           , _ushort               , unsigned short         )
    //_RCPPGSL_SPEC(unsigned long          , _ulong                , unsigned long          )
    _RCPPGSL_SPEC(char                     , _char                 , unsigned char          )
    _RCPPGSL_SPEC(gsl_complex              , _complex              , gsl_complex            )
    _RCPPGSL_SPEC(gsl_complex_float        , _complex_float        , gsl_complex_float      )
    _RCPPGSL_SPEC(gsl_complex_long_double  , _complex_long_double  , gsl_complex_long_double)
    
    #undef _RCPPGSL_SPEC
    #undef _RCPPGSL_SPEC_NOSUFFIX


    template <typename T> class vector_view {
    public:
        struct internal_view
        {
            const gsl_vector vector;
            
            inline internal_view(const gsl_vector &v) : vector(v) {}
        };
        
        typedef typename vector<T>::type type;
        typedef typename vector<T>::const_iterator const_iterator;
        
        typedef typename vector<T>::gsltype gsltype;
        typedef typename vector_view_type<T>::type view_type;
        typedef typename vector_view_type<T>::const_type const_view_type;
        typedef typename vector<T>::ConstProxy ConstProxy;
        
        vector_view(view_type v) : view(v.vector) {}
        vector_view(const_view_type v) : view(v.vector) {}
        inline ConstProxy operator[](int i) { 
            return ConstProxy(&view.vector, i);
        }
        inline const_iterator begin() const {
            return const_iterator(ConstProxy(&view.vector, 0));
        }
        inline const_iterator end() const {
            return const_iterator(ConstProxy(&view.vector, view.vector.size));
        }
        inline size_t size() const { return view.vector.size; }
        inline operator const gsltype*() { return &view.vector; }
    
        internal_view view;
    };

    template <typename T> class matrix_view {
    public:
        struct internal_view
        {
            const gsl_matrix matrix;
            
            inline internal_view(const gsl_matrix &m) : matrix(m) {}
        };
        
        typedef typename matrix<T>::type type;
        typedef typename matrix<T>::gsltype gsltype;
        typedef typename matrix_view_type<T>::type view_type;
        typedef typename matrix_view_type<T>::const_type const_view_type;
        typedef typename matrix<T>::ConstProxy ConstProxy;
    
        matrix_view(view_type v) : view(v.matrix) {} 
        matrix_view(const_view_type v) : view(v.matrix) {}
        inline ConstProxy operator()(int row, int col) {
            return ConstProxy(&view.matrix, row, col);
        }
        inline size_t nrow() const { return view.matrix.size1; }              
        inline size_t ncol() const { return view.matrix.size2; }              
        inline size_t size() const { return view.matrix.size1 * view.matrix.size2; }
        inline operator const gsltype*() { return &view.matrix; }
        
        internal_view view;
    };
}


/* forward declarations */
namespace Rcpp {

    #undef _RCPPGSL_WRAPDEF
    #define _RCPPGSL_WRAPDEF(__SUFFIX__)                                     \
    template<> inline SEXP wrap(const gsl_vector##__SUFFIX__&);              \
    template<> inline SEXP wrap(const gsl_vector##__SUFFIX__##_view&);       \
    template<> inline SEXP wrap(const gsl_vector##__SUFFIX__##_const_view&); \
    template<> inline SEXP wrap(const gsl_matrix##__SUFFIX__&);              \
    template<> inline SEXP wrap(const gsl_matrix##__SUFFIX__##_view&);       \
    template<> inline SEXP wrap(const gsl_matrix##__SUFFIX__##_const_view&);

    _RCPPGSL_WRAPDEF(_int) 
    _RCPPGSL_WRAPDEF(_float) 
    _RCPPGSL_WRAPDEF(_long) 
    _RCPPGSL_WRAPDEF(_char) 
    _RCPPGSL_WRAPDEF(_complex) 
    _RCPPGSL_WRAPDEF(_complex_float) 
    _RCPPGSL_WRAPDEF(_complex_long_double) 
    _RCPPGSL_WRAPDEF(_long_double) 
    _RCPPGSL_WRAPDEF(_short) 
    _RCPPGSL_WRAPDEF(_uchar) 
    _RCPPGSL_WRAPDEF(_uint) 
    _RCPPGSL_WRAPDEF(_ushort) 
    _RCPPGSL_WRAPDEF(_ulong) 

    template<> inline SEXP wrap(const gsl_vector&);                
    template<> inline SEXP wrap(const gsl_vector_view&);         
    template<> inline SEXP wrap(const gsl_vector_const_view&);   
    template<> inline SEXP wrap(const gsl_matrix&);                
    template<> inline SEXP wrap(const gsl_matrix_view&);         
    template<> inline SEXP wrap(const gsl_matrix_const_view&);

    template <typename T> SEXP wrap(const ::RcppGSL::vector<T>&);
    template <typename T> SEXP wrap(const ::RcppGSL::matrix<T>&);
    
    template <typename T> SEXP wrap(const ::RcppGSL::vector_view<T>&);
    template <typename T> SEXP wrap(const ::RcppGSL::matrix_view<T>&);
    
}

#endif
