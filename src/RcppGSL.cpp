#include <RcppGSL.h>

using namespace Rcpp ;

extern "C" SEXP test_gsl_vector(){
	gsl_vector * x_double = gsl_vector_calloc (10);
	gsl_vector_float * x_float = gsl_vector_float_calloc(10) ;
	gsl_vector_int * x_int  = gsl_vector_int_calloc(10) ;
	gsl_vector_long * x_long  = gsl_vector_long_calloc(10) ;
	gsl_vector_char * x_char  = gsl_vector_char_calloc(10) ;
	gsl_vector_complex * x_complex  = gsl_vector_complex_calloc(10) ;
	gsl_vector_complex_float * x_complex_float  = gsl_vector_complex_float_calloc(10) ;
	gsl_vector_complex_long_double * x_complex_long_double  = gsl_vector_complex_long_double_calloc(10) ;
	gsl_vector_long_double * x_long_double  = gsl_vector_long_double_calloc(10) ;
	gsl_vector_short * x_short  = gsl_vector_short_calloc(10) ;
	gsl_vector_uchar * x_uchar  = gsl_vector_uchar_calloc(10) ;
	gsl_vector_uint * x_uint  = gsl_vector_uint_calloc(10) ;
	gsl_vector_ushort * x_ushort  = gsl_vector_ushort_calloc(10) ;
	gsl_vector_ulong * x_ulong  = gsl_vector_ulong_calloc(10) ;
	
	/* create an R list containing copies of gsl data */
	List res = List::create( 
		_["gsl_vector"] = *x_double, 
		_["gsl_vector_float"] = *x_float, 
		_["gsl_vector_int"] = *x_int, 
		_["gsl_vector_long"] = *x_long, 
		_["gsl_vector_char"] = *x_char, 
		_["gsl_vector_complex"] = *x_complex,
		_["gsl_vector_complex_float"] = *x_complex_float, 
		_["gsl_vector_complex_long_double"] = *x_complex_long_double, 
		_["gsl_vector_long_double"] = *x_long_double, 
		_["gsl_vector_short"] = *x_short, 
		_["gsl_vector_uchar"] = *x_uchar, 
		_["gsl_vector_uint"] = *x_uint, 
		_["gsl_vector_ushort"] = *x_ushort, 
		_["gsl_vector_ulong"] = *x_ulong
		) ;
	
	/* cleanup gsl data */
	gsl_vector_free(x_double);
	gsl_vector_float_free( x_float);
	gsl_vector_int_free( x_int );
	gsl_vector_long_free( x_long );
	gsl_vector_char_free( x_char );
	gsl_vector_complex_free( x_complex );
	gsl_vector_complex_float_free( x_complex_float );
	gsl_vector_complex_long_double_free( x_complex_long_double );
	gsl_vector_long_double_free( x_long_double );
	gsl_vector_short_free( x_short );
	gsl_vector_uchar_free( x_uchar );
	gsl_vector_uint_free( x_uint );
	gsl_vector_ushort_free( x_ushort );
	gsl_vector_ulong_free( x_ulong );
	
	return res ;
}

extern "C" SEXP test_gsl_matrix(){
	gsl_matrix * x_double                                   = gsl_matrix_alloc(5, 2);                      gsl_matrix_set_identity( x_double ) ;
	gsl_matrix_float * x_float                              = gsl_matrix_float_alloc(5,2) ;                gsl_matrix_float_set_identity( x_float ) ;
	gsl_matrix_int * x_int                                  = gsl_matrix_int_alloc(5,2) ;                  gsl_matrix_int_set_identity( x_int ) ;
	gsl_matrix_long * x_long                                = gsl_matrix_long_alloc(5,2) ;                 gsl_matrix_long_set_identity( x_long ) ;
	gsl_matrix_char * x_char                                = gsl_matrix_char_alloc(5,2) ;                 gsl_matrix_char_set_identity( x_char ) ;
	gsl_matrix_complex * x_complex                          = gsl_matrix_complex_alloc(5,2) ;              gsl_matrix_complex_set_identity( x_complex ) ;
	gsl_matrix_complex_float * x_complex_float              = gsl_matrix_complex_float_alloc(5,2) ;        gsl_matrix_complex_float_set_identity( x_complex_float ) ;
	gsl_matrix_complex_long_double * x_complex_long_double  = gsl_matrix_complex_long_double_alloc(5,2) ;  gsl_matrix_complex_long_double_set_identity( x_complex_long_double ) ;
	gsl_matrix_long_double * x_long_double                  = gsl_matrix_long_double_alloc(5,2) ;          gsl_matrix_long_double_set_identity( x_long_double ) ;
	gsl_matrix_short * x_short                              = gsl_matrix_short_alloc(5,2) ;                gsl_matrix_short_set_identity( x_short ) ;
	gsl_matrix_uchar * x_uchar                              = gsl_matrix_uchar_alloc(5,2) ;                gsl_matrix_uchar_set_identity( x_uchar ) ;
	gsl_matrix_uint * x_uint                                = gsl_matrix_uint_alloc(5,2) ;                 gsl_matrix_uint_set_identity( x_uint) ;
	gsl_matrix_ushort * x_ushort                            = gsl_matrix_ushort_alloc(5,2) ;               gsl_matrix_ushort_set_identity( x_ushort ) ;
	gsl_matrix_ulong * x_ulong                              = gsl_matrix_ulong_alloc(5,2) ;                gsl_matrix_ulong_set_identity( x_ulong ) ;
	
	List res = List::create( 
		_["gsl_matrix"] = *x_double , 
		_["gsl_matrix_float"] = *x_float, 
		_["gsl_matrix_int"] = *x_int, 
		_["gsl_matrix_long"] = *x_long, 
		_["gsl_matrix_char"] = *x_char, 
		_["gsl_matrix_complex"] = *x_complex,
		_["gsl_matrix_complex_float"] = *x_complex_float, 
		_["gsl_matrix_complex_long_double"] = *x_complex_long_double, 
		_["gsl_matrix_long_double"] = *x_long_double, 
		_["gsl_matrix_short"] = *x_short, 
		_["gsl_matrix_uchar"] = *x_uchar, 
		_["gsl_matrix_uint"] = *x_uint, 
		_["gsl_matrix_ushort"] = *x_ushort, 
		_["gsl_matrix_ulong"] = *x_ulong
		) ;
	
	gsl_matrix_free( x_double );
	gsl_matrix_float_free( x_float);
	gsl_matrix_int_free( x_int );
	gsl_matrix_long_free( x_long );
	gsl_matrix_char_free( x_char );
	gsl_matrix_complex_free( x_complex );
	gsl_matrix_complex_float_free( x_complex_float );
	gsl_matrix_complex_long_double_free( x_complex_long_double );
	gsl_matrix_long_double_free( x_long_double );
	gsl_matrix_short_free( x_short );
	gsl_matrix_uchar_free( x_uchar );
	gsl_matrix_uint_free( x_uint );
	gsl_matrix_ushort_free( x_ushort );
	gsl_matrix_ulong_free( x_ulong );
	
	return res ;
}

extern "C" SEXP test_gsl_vector_view(){
	int n = 10 ;
	gsl_vector *v = gsl_vector_calloc (n);
	for( int i=0 ; i<n; i++){
		gsl_vector_set( v, i, i ) ;	
	}
	gsl_vector_view v_even = gsl_vector_subvector_with_stride(v, 0, 2, n/2);
    gsl_vector_view v_odd  = gsl_vector_subvector_with_stride(v, 1, 2, n/2);
    
    List res = List::create( 
    	_["even"] = v_even, 
    	_["odd" ] = v_odd
    	) ;
    gsl_vector_free(v);
	
    return res ;
}
