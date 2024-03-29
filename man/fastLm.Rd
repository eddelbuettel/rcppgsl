\name{fastLm}
\alias{fastLm}
\alias{fastLmPure}
\alias{fastLm.default}
\alias{fastLm.formula}
\concept{regression}
\title{Bare-bones linear model fitting function}
\description{
  \code{fastLm} estimates the linear model using the \code{gsl_multifit_linear}
  function of the \code{GNU GSL} library.
}
\usage{
fastLmPure(X, y)

fastLm(X, \dots)
\method{fastLm}{default}(X, y, \dots)
\method{fastLm}{formula}(formula, data = list(), \dots)
}
\arguments{
  \item{y}{a vector containing the explained variable.}
  \item{X}{a model matrix.}
  \item{formula}{a symbolic description of the model to be fit.}
  \item{data}{an optional data frame containing the variables in the model.}
  \item{\ldots}{not used}
}
\details{
  Linear models should be estimated using the \code{\link{lm}} function. In
  some cases, \code{\link{lm.fit}} may be appropriate.

  The \code{fastLmPure} function provides a reference use case of the \code{GSL}
  library via the wrapper functions in the \pkg{RcppGSL} package.
  
  The \code{fastLm} function provides a more standard implementation of
  a linear model fit, offering both a default and a formula interface as
  well as \code{print}, \code{summary} and \code{predict} methods.

  Lastly, one must be be careful in timing comparisons of
  \code{\link{lm}} and friends versus this approach based on \code{GSL}
  or \code{Armadillo}. The reason that \code{GSL} or \code{Armadillo} can
  do something like \code{\link{lm.fit}} faster than the functions in
  the stats package is because they use the Lapack version
  of the QR decomposition while the stats package uses a \emph{modified}
  Linpack version.  Hence \code{GSL} and \code{Armadillo} uses level-3 BLAS code
  whereas the stats package uses level-1 BLAS.  However,
  \code{GSL} or \code{Armadillo} will choke on rank-deficient model matrices whereas
  the functions from the stats package will handle them properly due to
  the modified Linpack code.  Statisticians want a pivoting scheme of
  \dQuote{pivot only on (apparent) rank deficiency} and numerical
  analysts have no idea why statisticians want this so it is not part of
  conventional linear algebra software.
}

\value{
  \code{fastLmPure} returns a list with three components:
  \item{coefficients}{a vector of coefficients}
  \item{stderr}{a vector of the (estimated) standard errors of the coefficient estimates}
  \item{df}{a scalar denoting the degrees of freedom in the model}
  
  \code{fastLm} returns a richer object which also includes the
  residuals and call similar to the \code{\link{lm}} or
  \code{\link[MASS]{rlm}} functions..
}
\seealso{\code{\link{lm}}, \code{\link{lm.fit}}} 
\references{GNU GSL project: \url{https://www.gnu.org/software/gsl/}}
\author{
  The GNU GSL library is being written by team of authors with the
  overall development, design and implementation lead by Brian Gough and
  Gerard Jungman.  RcppGSL is written by Romain Francois and Dirk Eddelbuettel.
}
\examples{
  data(trees, package="datasets")

  ## bare-bones direct interface
  flm <- fastLmPure( cbind(1, log(trees$Girth)), log(trees$Volume) )
  print(flm)

  ## standard R interface for formula or data returning object of class fastLm
  flmmod <- fastLm( log(Volume) ~ log(Girth), data=trees)
  summary(flmmod)

}
\keyword{regression}

