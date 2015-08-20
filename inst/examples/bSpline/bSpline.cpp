// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

// [[Rcpp::depends(RcppGSL)]]
#include <RcppGSL.h>

#include <gsl/gsl_bspline.h>
#include <gsl/gsl_multifit.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_randist.h>
#include <gsl/gsl_statistics.h>

const int N = 200;                              // number of data points to fit 
const int NCOEFFS = 12;                         // number of fit coefficients */
const int NBREAK = (NCOEFFS - 2);               // ncoeffs + 2 - k = ncoeffs - 2 as k = 4 */

// [[Rcpp::export]]
Rcpp::List genData() {
    const size_t n = N;
    size_t i;
    RcppGSL::Vector w(n), x(n), y(n);

    gsl_rng_env_setup();
    gsl_rng *r = gsl_rng_alloc(gsl_rng_default);
    //printf("#m=0,S=0\n");

    for (i = 0; i < n; ++i) {      /* this is the data to be fitted */
        double xi = (15.0 / (N - 1)) * i;
        double yi = cos(xi) * exp(-0.1 * xi);

        double sigma = 0.1 * yi;
        double dy = gsl_ran_gaussian(r, sigma);
        yi += dy;

        x[i] = xi;  // instead of  gsl_vector_set(x, i, xi);
        y[i] = yi;  // instead of  gsl_vector_set(y, i, yi);
        w[i] = 1.0 / (sigma * sigma);    // gsl_vector_set(w, i, 1.0 / (sigma * sigma));
        //printf("%f %f\n", xi, yi);
    }

    gsl_rng_free(r);
    
    return Rcpp::DataFrame::create(Rcpp::Named("x") = x,
                                   Rcpp::Named("y") = y,
                                   Rcpp::Named("w") = w);
}



// [[Rcpp::export]]
Rcpp::List fitData(Rcpp::DataFrame D) {

    const size_t ncoeffs = NCOEFFS;
    const size_t nbreak = NBREAK;

    const size_t n = N;
    size_t i, j;

    RcppGSL::Vector y = D["y"];		// access columns by name, 
    RcppGSL::Vector x = D["x"];		// assigning to GSL vectors
    RcppGSL::Vector w = D["w"];

    gsl_bspline_workspace *bw;
    RcppGSL::Vector B(ncoeffs);
    RcppGSL::Vector c(ncoeffs);
    RcppGSL::Matrix X(n, ncoeffs);
    RcppGSL::Matrix cov(ncoeffs, ncoeffs);
    gsl_multifit_linear_workspace *mw;
    double chisq, Rsq, dof, tss;

    bw = gsl_bspline_alloc(4, nbreak);	    // allocate a cubic bspline workspace (k = 4)
    mw = gsl_multifit_linear_alloc(n, ncoeffs);

    gsl_bspline_knots_uniform(0.0, 15.0, bw);	// use uniform breakpoints on [0, 15] 

    for (i = 0; i < n; ++i) {			// construct the fit matrix X 
        double xi = x[i];       // gsl_vector_get(x, i);

        gsl_bspline_eval(xi, B, bw);		// compute B_j(xi) for all j 

        for (j = 0; j < ncoeffs; ++j) {		// fill in row i of X 
            double Bj = B[j];  // gsl_vector_get(B, j);
            X(i,j) = Bj;       // gsl_matrix_set(X, i, j, Bj);
        }
    }

    gsl_multifit_wlinear(X, w, y, c, cov, &chisq, mw);  // do the fit 
    
    dof = n - ncoeffs;
    tss = gsl_stats_wtss(w->data, 1, y->data, 1, y->size);
    Rsq = 1.0 - chisq / tss;
    
    Rcpp::NumericVector FX(151), FY(151);	// output the smoothed curve 
    double xi, yi, yerr;
    for (xi = 0.0, i=0; xi < 15.0; xi += 0.1, i++) {
        gsl_bspline_eval(xi, B, bw);
        gsl_multifit_linear_est(B, c, cov, &yi, &yerr);
        FX[i] = xi;
        FY[i] = yi;
    }

    gsl_bspline_free(bw);
    gsl_multifit_linear_free(mw);
   
    return Rcpp::List::create(Rcpp::Named("X") = FX,
                              Rcpp::Named("Y") = FY,
                              Rcpp::Named("chisqdof") = Rcpp::wrap(chisq/dof),
                              Rcpp::Named("rsq") = Rcpp::wrap(Rsq));

}

