#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP RcppGSL_fastLm(SEXP, SEXP);
extern SEXP RcppGSL_gslResetErrorHandler(void);
extern SEXP RcppGSL_gslSetErrorHandlerOff(void);

static const R_CallMethodDef CallEntries[] = {
    {"RcppGSL_fastLm",                (DL_FUNC) &RcppGSL_fastLm,                2},
    {"RcppGSL_gslResetErrorHandler",  (DL_FUNC) &RcppGSL_gslResetErrorHandler,  0},
    {"RcppGSL_gslSetErrorHandlerOff", (DL_FUNC) &RcppGSL_gslSetErrorHandlerOff, 0},
    {NULL, NULL, 0}
};

void R_init_RcppGSL(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
