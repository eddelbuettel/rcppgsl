// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-
//
// gsl.cpp: RcppGSL R integration of GSL via Rcpp -- unit tests
//
// Copyright (C) 2010 - 2013  Romain Francois and Dirk Eddelbuettel
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

using namespace Rcpp;

// [[Rcpp::depends(RcppGSL)]]

// [[Rcpp::export]]
List test_gsl_vector_wrapper() {
    RcppGSL::vector<double> x_double( 10 );
    RcppGSL::vector<float> x_float( 10 );
    RcppGSL::vector<int> x_int( 10 );
    //RcppGSL::vector<long> x_long( 10 );
    RcppGSL::vector<char> x_char( 10 );
    RcppGSL::vector<long double> x_long_double( 10 );
    RcppGSL::vector<short> x_short( 10 );
    RcppGSL::vector<unsigned char> x_uchar( 10 );
    RcppGSL::vector<unsigned int> x_uint( 10 );
    RcppGSL::vector<unsigned short> x_ushort( 10 );
    //RcppGSL::vector<unsigned long> x_ulong( 10 );
    RcppGSL::vector<gsl_complex> x_complex( 10 );
    RcppGSL::vector<gsl_complex_float> x_complex_float( 10 );
    RcppGSL::vector<gsl_complex_long_double> x_complex_long_double( 10 );

    List res = List::create(_["gsl_vector"] = x_double,
			    _["gsl_vector_float"] = x_float,
			    _["gsl_vector_int"] = x_int,
			    //_["gsl_vector_long"] = x_long,
			    _["gsl_vector_char"] = x_char,
			    _["gsl_vector_complex"] = x_complex,
			    _["gsl_vector_complex_float"] = x_complex_float,
			    _["gsl_vector_complex_long_double"] = x_complex_long_double,
			    _["gsl_vector_long_double"] = x_long_double,
			    _["gsl_vector_short"] = x_short,
			    _["gsl_vector_uchar"] = x_uchar,
			    _["gsl_vector_uint"] = x_uint,
			    _["gsl_vector_ushort"] = x_ushort
			    //,_["gsl_vector_ulong"] = x_ulong
			    );

    x_double.free();
    x_float.free();
    x_int.free();
    //x_long.free();
    x_char.free();
    x_long_double.free();
    x_short.free();
    x_uchar.free();
    x_uint.free();
    x_ushort.free();
    //x_ulong.free();
    x_complex.free();
    x_complex_float.free();
    x_complex_long_double.free();
    
    return res;
}

// [[Rcpp::export]]
List test_gsl_vector() {
    gsl_vector * x_double = gsl_vector_calloc (10);
    gsl_vector_float * x_float = gsl_vector_float_calloc(10);
    gsl_vector_int * x_int  = gsl_vector_int_calloc(10);
    //gsl_vector_long * x_long  = gsl_vector_long_calloc(10);
    gsl_vector_char * x_char  = gsl_vector_char_calloc(10);
    gsl_vector_complex * x_complex  = gsl_vector_complex_calloc(10);
    gsl_vector_complex_float * x_complex_float  = gsl_vector_complex_float_calloc(10);
    gsl_vector_complex_long_double * x_complex_long_double  = gsl_vector_complex_long_double_calloc(10);
    gsl_vector_long_double * x_long_double  = gsl_vector_long_double_calloc(10);
    gsl_vector_short * x_short  = gsl_vector_short_calloc(10);
    gsl_vector_uchar * x_uchar  = gsl_vector_uchar_calloc(10);
    gsl_vector_uint * x_uint  = gsl_vector_uint_calloc(10);
    gsl_vector_ushort * x_ushort  = gsl_vector_ushort_calloc(10);
    //gsl_vector_ulong * x_ulong  = gsl_vector_ulong_calloc(10);

    /* create an R list containing copies of gsl data */
    List res = List::create(_["gsl_vector"] = *x_double,
			    _["gsl_vector_float"] = *x_float,
			    _["gsl_vector_int"] = *x_int,
			    //_["gsl_vector_long"] = *x_long,
			    _["gsl_vector_char"] = *x_char,
			    _["gsl_vector_complex"] = *x_complex,
			    _["gsl_vector_complex_float"] = *x_complex_float,
			    _["gsl_vector_complex_long_double"] = *x_complex_long_double,
			    _["gsl_vector_long_double"] = *x_long_double,
			    _["gsl_vector_short"] = *x_short,
			    _["gsl_vector_uchar"] = *x_uchar,
			    _["gsl_vector_uint"] = *x_uint,
			    _["gsl_vector_ushort"] = *x_ushort
			    //,_["gsl_vector_ulong"] = *x_ulong
			    );

    /* cleanup gsl data */
    gsl_vector_free(x_double);
    gsl_vector_float_free( x_float);
    gsl_vector_int_free( x_int );
    //gsl_vector_long_free( x_long );
    gsl_vector_char_free( x_char );
    gsl_vector_complex_free( x_complex );
    gsl_vector_complex_float_free( x_complex_float );
    gsl_vector_complex_long_double_free( x_complex_long_double );
    gsl_vector_long_double_free( x_long_double );
    gsl_vector_short_free( x_short );
    gsl_vector_uchar_free( x_uchar );
    gsl_vector_uint_free( x_uint );
    gsl_vector_ushort_free( x_ushort );
    //gsl_vector_ulong_free( x_ulong );
    
    return res;
}

// [[Rcpp::export]]
List test_gsl_matrix() {
    gsl_matrix * x_double                                   = gsl_matrix_alloc(5, 2);
    gsl_matrix_set_identity( x_double );
    gsl_matrix_float * x_float                              = gsl_matrix_float_alloc(5,2);
    gsl_matrix_float_set_identity( x_float );
    gsl_matrix_int * x_int                                  = gsl_matrix_int_alloc(5,2);
    gsl_matrix_int_set_identity( x_int );
    //gsl_matrix_long * x_long                                = gsl_matrix_long_alloc(5,2);
    //gsl_matrix_long_set_identity( x_long );
    gsl_matrix_char * x_char                                = gsl_matrix_char_alloc(5,2);
    gsl_matrix_char_set_identity( x_char );
    gsl_matrix_complex * x_complex                          = gsl_matrix_complex_alloc(5,2);
    gsl_matrix_complex_set_identity( x_complex );
    gsl_matrix_complex_float * x_complex_float              = gsl_matrix_complex_float_alloc(5,2);
    gsl_matrix_complex_float_set_identity( x_complex_float );
    gsl_matrix_complex_long_double * x_complex_long_double  = gsl_matrix_complex_long_double_alloc(5,2);  
    gsl_matrix_complex_long_double_set_identity( x_complex_long_double );
    gsl_matrix_long_double * x_long_double                  = gsl_matrix_long_double_alloc(5,2);
    gsl_matrix_long_double_set_identity( x_long_double );
    gsl_matrix_short * x_short                              = gsl_matrix_short_alloc(5,2);
    gsl_matrix_short_set_identity( x_short );
    gsl_matrix_uchar * x_uchar                              = gsl_matrix_uchar_alloc(5,2);
    gsl_matrix_uchar_set_identity( x_uchar );
    gsl_matrix_uint * x_uint                                = gsl_matrix_uint_alloc(5,2);
    gsl_matrix_uint_set_identity( x_uint);
    gsl_matrix_ushort * x_ushort                            = gsl_matrix_ushort_alloc(5,2);
    gsl_matrix_ushort_set_identity( x_ushort );
    //gsl_matrix_ulong * x_ulong                            = gsl_matrix_ulong_alloc(5,2);
    //gsl_matrix_ulong_set_identity( x_ulong );

    List res = List::create(_["gsl_matrix"] = *x_double ,
			    _["gsl_matrix_float"] = *x_float,
			    _["gsl_matrix_int"] = *x_int,
			    //_["gsl_matrix_long"] = *x_long,
			    _["gsl_matrix_char"] = *x_char,
			    _["gsl_matrix_complex"] = *x_complex,
			    _["gsl_matrix_complex_float"] = *x_complex_float,
			    _["gsl_matrix_complex_long_double"] = *x_complex_long_double,
			    _["gsl_matrix_long_double"] = *x_long_double,
			    _["gsl_matrix_short"] = *x_short,
			    _["gsl_matrix_uchar"] = *x_uchar,
			    _["gsl_matrix_uint"] = *x_uint,
			    _["gsl_matrix_ushort"] = *x_ushort
			    //,_["gsl_matrix_ulong"] = *x_ulong
			    );

    gsl_matrix_free( x_double );
    gsl_matrix_float_free( x_float);
    gsl_matrix_int_free( x_int );
    //gsl_matrix_long_free( x_long );
    gsl_matrix_char_free( x_char );
    gsl_matrix_complex_free( x_complex );
    gsl_matrix_complex_float_free( x_complex_float );
    gsl_matrix_complex_long_double_free( x_complex_long_double );
    gsl_matrix_long_double_free( x_long_double );
    gsl_matrix_short_free( x_short );
    gsl_matrix_uchar_free( x_uchar );
    gsl_matrix_uint_free( x_uint );
    gsl_matrix_ushort_free( x_ushort );
    //gsl_matrix_ulong_free( x_ulong );
    
    return res;
}

// [[Rcpp::export]]
List test_gsl_vector_view() {
    int n = 10;
    gsl_vector *v = gsl_vector_calloc (n);
    for( int i=0; i<n; i++){
	gsl_vector_set( v, i, i );
    }
    gsl_vector_view v_even = gsl_vector_subvector_with_stride(v, 0, 2, n/2);
    gsl_vector_view v_odd  = gsl_vector_subvector_with_stride(v, 1, 2, n/2);

    List res = List::create(_["even"] = v_even,
			    _["odd" ] = v_odd);
    gsl_vector_free(v);

    return res;
}

// [[Rcpp::export]]
List test_gsl_matrix_view() {
    int nrow = 4;
    int ncol = 6;
    gsl_matrix *m = gsl_matrix_alloc(nrow, ncol);
    int k =0;
    for( int i=0; i<nrow; i++){
	for( int j=0; j<ncol; j++, k++){
	    gsl_matrix_set( m, i, j, k );
	}
    }
    gsl_matrix_view x = gsl_matrix_submatrix(m, 2, 2, 2, 2 );

    List res = List::create(_["full"] = *m,
			    _["view"] = x);
    gsl_matrix_free(m);

    return res;
}

// [[Rcpp::export]]
double test_gsl_vector_input(NumericVector vec_) {
    RcppGSL::vector<double> vec = as< RcppGSL::vector<double> >(vec_);
    int n = vec->size;
    double res = 0.0;
    for( int i=0; i<n; i++){
	res += gsl_vector_get( vec, i );
    }
    vec.free();
    return res;
}

// [[Rcpp::export]]
double test_gsl_matrix_input(NumericMatrix mat_) {
    RcppGSL::matrix<double> mat = as< RcppGSL::matrix<double> >( mat_);
    int nr = mat->size1;

    double res = 0.0;
    for( int i=0; i<nr; i++){
	res += mat( i, 0 );
    }
    mat.free();
    return res;
}

// [[Rcpp::export]]
IntegerVector test_gsl_vector_conv() { 
    RcppGSL::vector<int> vec(10);
    for( int i=0; i<10; i++){
	gsl_vector_int_set( vec, i, i );
    }
    Rcpp::IntegerVector x;
    x = vec;
    return x;
}

// [[Rcpp::export]]
NumericVector test_gsl_vector_indexing(NumericVector vec_) {
    RcppGSL::vector<double> vec = as< RcppGSL::vector<double> >(vec_);
    for( size_t i=0; i< vec.size(); i++){
	vec[i] = vec[i] + 1.0;
    }
    NumericVector res = Rcpp::wrap( vec );
    vec.free();
    return res;
}

// [[Rcpp::export]]
double test_gsl_vector_iterating(NumericVector vec_) {
    RcppGSL::vector<double> vec = as< RcppGSL::vector<double> >(vec_);
    double res= std::accumulate( vec.begin(), vec.end(), 0.0 );
    vec.free();
    return res;
}

// [[Rcpp::export]]
NumericVector test_gsl_vector_iterator_transform(NumericVector vec_) {
    RcppGSL::vector<double> vec = as< RcppGSL::vector<double> >(vec_);
    NumericVector res(vec.size());
    std::transform(vec.begin(), vec.end(), res.begin(), ::sqrt);
    vec.free();
    return res;
}

// [[Rcpp::export]]
NumericMatrix test_gsl_matrix_indexing(NumericMatrix mat_) {
    RcppGSL::matrix<double> mat= as< RcppGSL::matrix<double> >( mat_ );
    for( size_t i=0; i< mat.nrow(); i++){
	for( size_t j=0; j< mat.ncol(); j++){
	    mat(i,j) = mat(i,j) + 1.0;
	}
    }
    Rcpp::NumericMatrix res = Rcpp::wrap(mat);
    mat.free();
    return res;
}

// [[Rcpp::export]]
List test_gsl_vector_view_wrapper() {
    int n = 10;
    RcppGSL::vector<double> vec( 10 );
    for( int i=0; i<n; i++){
	vec[i] = i;
    }
    RcppGSL::vector_view<double> v_even = gsl_vector_const_subvector_with_stride(vec, 0, 2, n/2);
    RcppGSL::vector_view<double> v_odd  = gsl_vector_const_subvector_with_stride(vec, 1, 2, n/2);

    List res = List::create(_["even"] = v_even,
			    _["odd" ] = v_odd);
    vec.free();

    return res;
}

// [[Rcpp::export]]
List test_gsl_matrix_view_wrapper() {
    int nrow = 4;
    int ncol = 6;
    RcppGSL::matrix<double> m(nrow, ncol);
    int k =0;
    for( int i=0; i<nrow; i++){
	for( int j=0; j<ncol; j++, k++){
	    m(i, j) = k;
	}
    }
    RcppGSL::matrix_view<double> x = gsl_matrix_const_submatrix(m, 2, 2, 2, 2 );

    List res = List::create(_["full"] = m,
			    _["view"] = x);
    m.free();

    return res;
}

// [[Rcpp::export]]
double test_gsl_vector_view_iterating(NumericVector vec_) {
    RcppGSL::vector<double> vec = as< RcppGSL::vector<double> >(vec_);
    int n = vec.size();
    RcppGSL::vector_view<double> v_even = gsl_vector_const_subvector_with_stride(vec, 0, 2, n/2);
    double res = std::accumulate( v_even.begin(), v_even.end(), 0.0 );
    return res;
}

// [[Rcpp::export]]
double test_gsl_matrix_view_indexing() {
    int nr = 10;
    int nc = 10;
    RcppGSL::matrix<double> mat( nr, nc );
    int k = 0;
    for( size_t i=0; i< mat.nrow(); i++){
	for( size_t j=0; j< mat.ncol(); j++, k++){
	    mat(i,j) = k;
	}
    }
    RcppGSL::matrix_view<double> x = gsl_matrix_const_submatrix(mat, 2, 2, 2, 2 );
    double res = 0.0;
    for( size_t i=0; i<x.nrow(); i++){
	for( size_t j=0; j<x.ncol(); j++){
	    res += x(i,j);
	}
    }
    mat.free();
    return res;
}
