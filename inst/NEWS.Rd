\name{NEWS}
\title{News for Package \pkg{RcppGSL}}
\newcommand{\cpkg}{\href{http://CRAN.R-project.org/package=#1}{\pkg{#1}}}

\section{Changes in version 0.2.6 (2015-xx-yy)}{
  \itemize{
    \item The RcppGSL matrix and vector class now keep track of object
    allocation and can therefore automatically free allocated object in
    the destructor. Explicit \code{x.free()} are still supported.
  }
}

\section{Changes in version 0.2.5 (2015-07-05)}{
  \itemize{
    \item The \code{colnorm} function in the included example package
    was rewritten to use Rcpp Attributes, the example package was
    updated and the version number increased to 0.0.3.
    \item The unit tests also use the updated version of the example
    package.
    \item The package, and the included example package, were updated
    throughout to conform to the current \code{R CMD check} standards.
    \item The RcppGSL-intro vignette was updated throughout.
    \item The Travis CI integration now uses r-cran-* packages which
    leads to faster tests.
  }
}

\section{Changes in version 0.2.4 (2015-01-24)}{
  \itemize{
    \item Two new helper function to turn the default GSL error handler
    off (and to restore it) were added. The default handler is now
    turned off when the package is attached so that GSL will no longer
    abort an R session on error. Users will have to check the error code.
    \item The \code{RcppGSL-intro.Rnw} vignette was expanded with a
    short section on the GSL error handler (thanks to Qiang Kou).
  }
}

\section{Changes in version 0.2.3 (2015-01-10)}{
  \itemize{
    \item The \code{src/Makevars.in} was pruned of GNU make features at
    the request of the CRAN Maintainers.
    \item \code{configure.ac} and \code{configure} were updated, and
    shortened.
    \item The \code{RcppGSL-intro.Rnw} vignette was updated for its look
    and feel.
  }
}

\section{Changes in version 0.2.2 (2014-05-31)}{
  \itemize{
    \item A subtle bug (tickled only by clang on some OS versions) in
    vector and matrix view initialization was corrected by Kevin Ushey 
  }
}

\section{Changes in version 0.2.1 (2014-05-26)}{
  \itemize{
    \item Added new example based on B-splines example in GSL manual
      illustrating simple GSL use via Rcpp attributes
    \item Vignette compilation has been reverted to using \pkg{highlight} 
      since version 0.4.2 or greater can be used as a vignette engine
      (with R 3.0.* or later). 
    \item Vignette compilation is now being done by \code{R CMD build}
      as R 3.0.0 supports different vignette engines, so the vignette
      build process has been simplified. A convenience helper script has
      also been added for command-line builds.
    \item Unit tests now use \code{sourceCpp()} instead of
    \code{cxxfunction()} from the \pkg{inline} package
    \item The \code{DESCRIPTION} file now uses \code{Suggests: Rcpp}
      (instead of \code{Depends: Rcpp}) to permit building of the
      vignette
    \item The package now takes advantage of the simplified build
      process available with Rcpp (>= 0.11.0)
    \item Similar updates to the build process were made for the example
      package included with RcppGSL
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
