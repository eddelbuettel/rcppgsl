.onLoad <- function(libname,pkgname){}

test_gsl_vector <- function(){
	.Call( "test_gsl_vector", PACKAGE = "RcppGSL" )
}
