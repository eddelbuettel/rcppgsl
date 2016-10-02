## RcppGSL [![Build Status](https://travis-ci.org/eddelbuettel/rcppgsl.svg)](https://travis-ci.org/eddelbuettel/rcppgsl) [![License](http://img.shields.io/badge/license-GPL%20%28%3E=%202%29-brightgreen.svg?style=flat)](http://www.gnu.org/licenses/gpl-2.0.html) [![CRAN](http://www.r-pkg.org/badges/version/RcppGSL)](https://cran.r-project.org/package=RcppGSL) [![Downloads](http://cranlogs.r-pkg.org/badges/RcppGSL?color=brightgreen)](http://www.r-pkg.org/pkg/RcppGSL)

This package uses [Rcpp](https://github.com/RcppCore/Rcpp) to connect the
[R](http://www.r-project.org) system to the
[GNU GSL](http://www.gnu.org/software/gsl/), a collection of numerical
routines for scientific computing, particularly its vector and matrix
classes.

### Examples

#### Faster `lm()` for OLS regression

The `fastLm()` function [included as file `src/fastLm.cpp`](https://github.com/eddelbuettel/rcppgsl/blob/master/src/fastLm.cpp) in the package:

```{.cpp}
#include <RcppGSL.h>

#include <gsl/gsl_multifit.h>
#include <cmath>

// [[Rcpp::export]]
Rcpp::List fastLm(const RcppGSL::Matrix &X, const RcppGSL::Vector &y) {

    int n = X.nrow(), k = X.ncol();
    double chisq;

    RcppGSL::Vector coef(k);                // to hold the coefficient vector 
    RcppGSL::Matrix cov(k,k);               // and the covariance matrix
    
    // the actual fit requires working memory we allocate and free
    gsl_multifit_linear_workspace *work = gsl_multifit_linear_alloc (n, k);
    gsl_multifit_linear (X, y, coef, cov, &chisq, work);
    gsl_multifit_linear_free (work);

    // assign diagonal to a vector, then take square roots to get std.error
    Rcpp::NumericVector std_err;
    std_err = gsl_matrix_diagonal(cov); 	// need two step decl. and assignment
    std_err = Rcpp::sqrt(std_err);         	// sqrt() is an Rcpp sugar function

    return Rcpp::List::create(Rcpp::Named("coefficients") = coef, 
                              Rcpp::Named("stderr")       = std_err,
                              Rcpp::Named("df.residual")  = n - k);
    
}

```

#### A simple column norm

This example comes from the [complete example package included in RcppGSL](https://github.com/eddelbuettel/rcppgsl/tree/master/inst/examples/RcppGSLExample)
and is from [the file `inst/examples/RcppGSLExample/src/colNorm.cpp`](https://github.com/eddelbuettel/rcppgsl/blob/master/inst/examples/RcppGSLExample/src/colNorm.cpp)

```{.cpp}

#include <RcppGSL.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

// [[Rcpp::export]]
Rcpp::NumericVector colNorm(const RcppGSL::Matrix & G) {
    int k = G.ncol();
    Rcpp::NumericVector n(k);           // to store results
    for (int j = 0; j < k; j++) {
        RcppGSL::VectorView colview = gsl_matrix_const_column (G, j);
        n[j] = gsl_blas_dnrm2(colview);
    }
    return n;                           // return vector
}

```

### Dependencies

- [GNU GSL](http://www.gnu.org/software/gsl/) library (eg [libgsl0-dev](https://packages.debian.org/sid/libgsl0-dev) on Debian or Ubuntu)
- [Rcpp](https://github.com/RcppCore/Rcpp) for seamless R and C++ integration

### Availabililty

On [CRAN](https://cran.r-project.org), here and on [its package page](http://dirk.eddelbuettel.com/code/rcpp.gsl.html).

### Authors

Dirk Eddelbuettel and Romain Francois

### License

GPL (>= 2)

