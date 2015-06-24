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
const int NBREAK = (NCOEFFS - 2);               // nbreak = ncoeffs + 2 - k = ncoeffs - 2 since k = 4 */

// [[Rcpp::export]]
Rcpp::List genData() {

    const size_t n = N;
    size_t i;
    double dy;
    gsl_rng *r;
    RcppGSL::vector<double> w(n), x(n), y(n);

    gsl_rng_env_setup();
    r = gsl_rng_alloc(gsl_rng_default);

    //printf("#m=0,S=0\n");
    /* this is the data to be fitted */

    for (i = 0; i < n; ++i) {
        double sigma;
        double xi = (15.0 / (N - 1)) * i;
        double yi = cos(xi) * exp(-0.1 * xi);

        sigma = 0.1 * yi;
        dy = gsl_ran_gaussian(r, sigma);
        yi += dy;

        gsl_vector_set(x, i, xi);
        gsl_vector_set(y, i, yi);
        gsl_vector_set(w, i, 1.0 / (sigma * sigma));
                
        //printf("%f %f\n", xi, yi);
    }

    Rcpp::DataFrame res = Rcpp::DataFrame::create(Rcpp::Named("x") = x,
                                                  Rcpp::Named("y") = y,
                                                  Rcpp::Named("w") = w);

    x.free();
    y.free();
    w.free();
    gsl_rng_free(r);

    return(res);
}



// [[Rcpp::export]]
Rcpp::List fitData(Rcpp::DataFrame D) {

    const size_t ncoeffs = NCOEFFS;
    const size_t nbreak = NBREAK;

    const size_t n = N;
    size_t i, j;

    RcppGSL::vector<double> y = D["y"];	// access columns by name, 
    RcppGSL::vector<double> x = D["x"];	// assigning to GSL vectors
    RcppGSL::vector<double> w = D["w"];

    gsl_bspline_workspace *bw;
    gsl_vector *B;
    gsl_vector *c; 
    gsl_matrix *X, *cov;
    gsl_multifit_linear_workspace *mw;
    double chisq, Rsq, dof, tss;

    bw = gsl_bspline_alloc(4, nbreak);	    // allocate a cubic bspline workspace (k = 4)
    B = gsl_vector_alloc(ncoeffs);

    X = gsl_matrix_alloc(n, ncoeffs);
    c = gsl_vector_alloc(ncoeffs);
    cov = gsl_matrix_alloc(ncoeffs, ncoeffs);
    mw = gsl_multifit_linear_alloc(n, ncoeffs);

    gsl_bspline_knots_uniform(0.0, 15.0, bw);	// use uniform breakpoints on [0, 15] 

    for (i = 0; i < n; ++i) {			// construct the fit matrix X 
        double xi = gsl_vector_get(x, i);

        gsl_bspline_eval(xi, B, bw);		// compute B_j(xi) for all j 

        for (j = 0; j < ncoeffs; ++j) {		// fill in row i of X 
            double Bj = gsl_vector_get(B, j);
            gsl_matrix_set(X, i, j, Bj);
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

    Rcpp::List res =
      Rcpp::List::create(Rcpp::Named("X")=FX,
                         Rcpp::Named("Y")=FY,
			 Rcpp::Named("chisqdof")=Rcpp::wrap(chisq/dof),
			 Rcpp::Named("rsq")=Rcpp::wrap(Rsq));

    gsl_bspline_free(bw);
    gsl_vector_free(B);
    gsl_matrix_free(X);
    gsl_vector_free(c);
    gsl_matrix_free(cov);
    gsl_multifit_linear_free(mw);
    
    y.free();
    x.free();
    w.free();

    return(res);   
}

