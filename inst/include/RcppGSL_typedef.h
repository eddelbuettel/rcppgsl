// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// RcppGSL_typedef.h: Shorthand Definitions for Seamless R and GSL Integration
//
// Copyright (C)  2015  Dirk Eddelbuettel
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

#ifndef RCPPGSL__TYPEDEF_H
#define RCPPGSL__TYPEDEF_H

namespace RcppGSL {

    typedef matrix<double> Matrix;
    typedef vector<double> Vector;

    typedef matrix_view<double> MatrixView;
    typedef vector_view<double> VectorView;

    
    typedef matrix<int> IntMatrix;
    typedef vector<int> IntVector;

    typedef matrix_view<int> IntMatrixView;
    typedef vector_view<int> IntVectorView;
    
}

#endif
