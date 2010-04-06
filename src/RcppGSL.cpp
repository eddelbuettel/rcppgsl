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
	
	/* create an R list containing copies of gsl data */
	List res = List::create( 
		_["gsl_vector"] = *x_double, 
		_["gsl_vector_float"] = *x_float, 
		_["gsl_vector_int"] = *x_int, 
		_["gsl_vector_long"] = *x_long, 
		_["gsl_vector_char"] = *x_char, 
		_["gsl_vector_complex"] = *x_complex,
		_["gsl_vector_complex_float"] = *x_complex_float
		) ;
	
	/* cleanup gsl data */
	gsl_vector_free(x_double);
	gsl_vector_float_free( x_float);
	gsl_vector_int_free( x_int );
	gsl_vector_long_free( x_long );
	gsl_vector_char_free( x_char );
	gsl_vector_complex_free( x_complex );
	gsl_vector_complex_float_free( x_complex_float );
	
	return res ;
}
