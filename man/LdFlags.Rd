\name{LdFlags}
\alias{LdFlags}
\alias{CFlags}
\title{Provide RcppGSL Compiler and Linker Flags}
\description{
  \code{LdFlags} and \code{CFlags} return the required flags and
  options for the compiler and system linker in order to build against
  GNU GSL. This allows portable use of \pkg{RcppGSL} (which needs the
  GNU GSL) as package location as well as operating-system specific
  details are abstracted away behind the interface of this function.

  \code{LdFlags} and \code{CFlags} are commonly called from the files
  \code{Makevars} (or \code{Makevars.win}) rather than in an interactive
  session. 
}
\usage{
LdFlags(print=TRUE)
RcppLdFlags(print=TRUE)
}
\arguments{
  \item{print}{A boolean determining whether the requested value is
  returned on the standard output, or silenly as a value.}
}
\value{
  A character vector suitable by use by the system compiler linker in order to
  compile and/or link against the GNU GSK.
}
\details{
  Thee functions are not meant to used interactively, and are intended
  solely for use by the build tools.

  The values that are returned are acquired by the package at load
  time. On Linux and OS X, the \code{pkg-config} program is queried. On
  Windows, environment variables used for GNU GSL builds with R are used.
}
\references{
  Dirk Eddelbuettel and Romain Francois (2011). \pkg{Rcpp}: Seamless R
  and C++ Integration. \emph{Journal of Statistical Software},
  \bold{40(8)}, 1-18. URL http://www.jstatsoft.org/v40/i08/ and
  available as \code{vignette("Rcpp-introduction")}.
}
\seealso{
  The document of the \code{pkg-config} system tool.
}
\author{Dirk Eddelbuettel and Romain Francois}
\keyword{programming}
\keyword{interface}
