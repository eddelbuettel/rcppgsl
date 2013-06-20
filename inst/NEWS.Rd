\name{NEWS}
\title{News for Package \pkg{RcppGSL}}
\newcommand{\cpkg}{\href{http://CRAN.R-project.org/package=#1}{\pkg{#1}}}

\section{Changes in version 0.2.1 (2013-xx-yy)}{
  \itemize{
    \item Added new example based on B-splines example in GSL manual
    illustrating simple GSL use via Rcpp attributes
    \item Vignette compilation has been reverted to using \pkg{highlight} 
    since version 0.4.2 or greater can be used as a vignette engine
    (with R 3.0.* or later). 
  }
}

\section{Changes in version 0.2.0 (2012-07-22)}{
  \itemize{
    \item{summary() for fastLm() now displays more information}
    \item{fastLmPure() now uses same argument order as R's lm.fit()}
    \item{Added more unit tests for fastLm() and related functions}
    \item{Export and document S3 methods in NAMESPACE and manual page as
      such}
    \item{Vignettes have been moved to the \code{vignettes/} directory}
    \item{Main vignette renamed to \code{RcppGSL-intro.pdf} to use a
      filename different from the package reference manual}
    \item{NEWS file converted to .Rd format}
    \item{inline plugin support function no longer uses
      assignInNamespace but deploys a small package-global enviornment}
  }
}
\section{Changes in version 0.1.1 (2011-04-05)}{
  \itemize{
    \item{Unit tests produce a summary vignette as for some of the other
      packages} 
    \item{The documentation Makefile now uses the $R_HOME environment
      variable} 
    \item{The documentation Makefile no longer calls clean in the all
      target} 
  }
}
\section{Changes in version 0.1.0 (2010-11-30)}{
  \itemize{
    \item{Initial CRAN release with basic functionality for vectors and
      matrices}
    \item{A vignette provides an introduction and documentation about
      the package}
    \item{An example package RcppGSLExample provides a complete stanza for
      creating your own package using RcppGSL (and the GSL and Rcpp)}
  }
}
