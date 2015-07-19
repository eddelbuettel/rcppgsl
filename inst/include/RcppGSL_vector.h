// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// RcppGSL.h: Rcpp/GSL glue
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

#ifndef RCPPGSL__RCPPGSL_VECTOR_H
#define RCPPGSL__RCPPGSL_VECTOR_H

#include <RcppGSLForward.h>
#include <Rcpp.h>

namespace RcppGSL {
    
    template <typename T> class gslvector_importer {
    public:
        typedef T r_import_type; /* this is important */
        
    private:
        r_import_type* data;
        int stride;
        int n;
        
    public:
        gslvector_importer(T* data_, int stride_, int n_) : data(data_), stride(stride_), n(n_) {}
        inline r_import_type get(int i) const {
            return data[ i * stride ];
        }
        inline int size() const { return n; }
    };
    
}

namespace Rcpp {

    #define RCPPGSL_WRAP(__TYPE__,__DATA__)                                             \
    template <> SEXP wrap(const __TYPE__& x) {                                          \
        return wrap(RcppGSL::gslvector_importer<__DATA__>(x.data, x.stride, x.size ) ); \
    } 

    #define RCPPGSL_WRAP_CAST(__TYPE__,__DATA__,__CAST__)                                                           \
    template <>  SEXP wrap(const __TYPE__& x) {                                                                     \
        return wrap(RcppGSL::gslvector_importer<__DATA__>(reinterpret_cast<__CAST__>(x.data), x.stride, x.size ) ); \
    } 

    RCPPGSL_WRAP(gsl_vector             ,double)
    RCPPGSL_WRAP(gsl_vector_float       ,float)
    RCPPGSL_WRAP(gsl_vector_int         ,int)
    RCPPGSL_WRAP(gsl_vector_long        ,long)
    RCPPGSL_WRAP(gsl_vector_long_double ,long double)
    RCPPGSL_WRAP(gsl_vector_short       ,short)
    RCPPGSL_WRAP(gsl_vector_uchar       ,unsigned char)
    RCPPGSL_WRAP(gsl_vector_uint        ,unsigned int)
    RCPPGSL_WRAP(gsl_vector_ushort      ,unsigned short)
    RCPPGSL_WRAP(gsl_vector_ulong       ,unsigned long)
    
    RCPPGSL_WRAP_CAST(gsl_vector_char               ,unsigned char          ,Rbyte* const)
    RCPPGSL_WRAP_CAST(gsl_vector_complex            ,gsl_complex            ,gsl_complex*)
    RCPPGSL_WRAP_CAST(gsl_vector_complex_float      ,gsl_complex_float      ,gsl_complex_float*)
    RCPPGSL_WRAP_CAST(gsl_vector_complex_long_double,gsl_complex_long_double,gsl_complex_long_double*)
    
    template <typename T> SEXP wrap(const ::RcppGSL::vector<T>& x) {
        return wrap(*(x.data));
    }

    #undef RCPPGSL_WRAP_CAST
    #undef RCPPGSL_WRAP

} 

#endif
