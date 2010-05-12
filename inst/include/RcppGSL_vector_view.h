// RcppGSL.h: Rcpp/GSL glue
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

#ifndef RCPPGSL__RCPPGSL_VECTOR_VIEW_H
#define RCPPGSL__RCPPGSL_VECTOR_VIEW_H

#include <RcppGSLForward.h>
#include <Rcpp.h>
#include <RcppGSL_caster.h> 

namespace Rcpp{

#define RCPPGSL_VIEW(SUFFIX)                                         \
template <> SEXP wrap( const gsl_vector##SUFFIX##_view& x){          \
	return wrap(x.vector) ;                                          \
}                                                                    \
template <> SEXP wrap( const gsl_vector##SUFFIX##_const_view& x ){   \
   return wrap(x.vector) ;                                           \
}

RCPPGSL_VIEW()
RCPPGSL_VIEW(_int)
RCPPGSL_VIEW(_float)
RCPPGSL_VIEW(_long)
RCPPGSL_VIEW(_char)
RCPPGSL_VIEW(_complex)
RCPPGSL_VIEW(_complex_float)
RCPPGSL_VIEW(_complex_long_double)
RCPPGSL_VIEW(_long_double)
RCPPGSL_VIEW(_short)
RCPPGSL_VIEW(_uchar)
RCPPGSL_VIEW(_uint)
RCPPGSL_VIEW(_ushort)
RCPPGSL_VIEW(_ulong)
#undef RCPPGSL_VIEW

} 

#endif
