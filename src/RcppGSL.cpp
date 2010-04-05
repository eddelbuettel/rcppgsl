#include <RcppGSL.h>

extern "C" SEXP test_gsl_vector(){
	gsl_vector * x = gsl_vector_alloc (10);
	gsl_vector_set_zero( x ) ;
	
	// we cannot have Rcpp::NumericVector xx = x ; 
	// because this does not involve the assignment operator
	// but the constructor and Vector only had templated assignement
	// operator, not templated constructor, so we have to do this in two steps
	Rcpp::NumericVector xx ;
	xx = *x  ;
	gsl_vector_free (x);
	return xx ;
}
