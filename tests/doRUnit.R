## doRUnit.R --- Run RUnit tests
##
## with credits to package fUtilities in RMetrics
## which credits Gregor Gojanc's example in CRAN package  'gdata'
## as per the (now deceased) R Wiki http://wiki.r-project.org/rwiki/doku.php?id=developers:runit
## and changed further by Martin Maechler
## and usage across several Rcpp* package
## and more changes by Murray Stokely in HistogramTools
##
## Dirk Eddelbuettel, 2010 - 2016

stopifnot(require("RUnit", quietly=TRUE))
stopifnot(require("RcppGSL", quietly=TRUE))

## Set a seed to make the test deterministic
set.seed(42)

## Define tests
testSuite <- defineTestSuite(name="RcppGSL Unit Tests",
                             dirs=system.file("unitTests", package = "RcppGSL"),
                             testFuncRegexp = "^[Tt]est.+")

## without this, we get (or used to get) unit test failures
Sys.setenv("R_TESTS"="")

## Run tests
tests <- runTestSuite(testSuite)

## Print results
printTextProtocol(tests)

## Return success or failure to R CMD CHECK
if (getErrors(tests)$nFail > 0) {
   stop("TEST FAILED!")
}
if (getErrors(tests)$nErr > 0) {
   stop("TEST HAD ERRORS!")
}
if (getErrors(tests)$nTestFunc < 1) {
   stop("NO TEST FUNCTIONS RUN!")
}
