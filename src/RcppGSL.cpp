#include <RcppGSL.h>

using namespace Rcpp ;

extern "C" SEXP test_gsl_vector(){
	gsl_vector * x_double = gsl_vector_calloc (10);
	gsl_vector_float * x_float = gsl_vector_float_calloc(10) ;
	
	/* create an R list containing copies of gsl data */
	List res = List::create( 
		_["gsl_vector"] = *x_double, 
		_["gsl_vector_float"] = *x_float 
		) ;
	
	/* cleanup gsl data */
	gsl_vector_free(x_double);
	gsl_vector_float_free( x_float);
	
	return res ;
}
