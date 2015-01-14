// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; tab-width: 4 -*-
//
// setErrorHandler.cpp: Set the GSL error handler
//
// Copyright (C)  2015         Dirk Eddelbuettel
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

#include <gsl/gsl_errno.h>

// See Chapter 3 of the GSL Reference manual on this

// Keep a pointer around in case someone wants to reset
static gsl_error_handler_t *ptr_gsl_error_handler_t = NULL;

// [[Rcpp::export]]
bool gslSetErrorHandlerOff() {
    ptr_gsl_error_handler_t = gsl_set_error_handler_off();
    return true;
}

// [[Rcpp::export]]
bool gslResetErrorHandler() {
    if (ptr_gsl_error_handler_t == NULL) {
        return false;
    }
    ptr_gsl_error_handler_t = gsl_set_error_handler(ptr_gsl_error_handler_t);
    return true;
}
