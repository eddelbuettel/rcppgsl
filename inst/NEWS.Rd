\name{NEWS}
\title{News for Package \pkg{RcppGSL}}
\newcommand{\ghpr}{\href{https://github.com/eddelbuettel/rcppgsl/pull/#1}{##1}}
\newcommand{\ghit}{\href{https://github.com/eddelbuettel/rcppgsl/issues/#1}{##1}}

\section{Changes in version 0.3.13 (2023-01-12)}{
  \itemize{
    \item Remove 'AC_PROG_CC' from 'configure.ac' per CRAN wish
  }
}

\section{Changes in version 0.3.12 (2022-10-30)}{
  \itemize{
    \item Two function prototypes were updated for \code{clang-15}.
    \item GitHub Actions were updated to checkout version 3.
  }
}

\section{Changes in version 0.3.11 (2022-03-12)}{
  \itemize{
    \item The UCRT Makefile was updated
    \item Minor edits to README.md were made
  }
}

\section{Changes in version 0.3.10 (2021-10-07)}{
  \itemize{
    \item Tests of the client package now skip if no LIB_GSL is set
    \item The \code{configure} files were updated to the standard of
    version 2.69 following a CRAN request
  }
}

\section{Changes in version 0.3.9 (2021-06-23)}{
  \itemize{
    \item The pdf vignette was extended by a small subsection (Dirk).
    \item The CI setup was updated to use \code{run.sh} from
    \href{https://eddelbuettel.github.io/r-ci/}{r-ci} (Dirk).
    \item The windows build was updated to GSL 2.7, and UCRT support was
    added (Jeroen in \ghpr{28}).
  }
}

\section{Changes in version 0.3.8 (2020-06-21)}{
  \itemize{
    \item A few missing \code{inline} statements were added to the
    headers fixing a (genuine) error that was seen only on Solaris (Dirk).
    \item The nice \code{colNorm} example is now in a file by itself,
    the previous versions are off in a new file \code{colNorm_old.cpp} (Dirk).
    \item The README.me now sports two new badges (Dirk).
    \item Travis CI was updated to 'bionic' and R 4.0 (Dirk).
  }
}

\section{Changes in version 0.3.7 (2019-10-20)}{
  \itemize{
    \item A logic error was corrected in the wrapper class, vector and matrix
    memory is now properly free()'ed (Dirk in \ghpr{22} fixing \ghpr{20}).
    \item The introductory vignettes is now premade (Dirk in \ghpr{23}), and
    was updated lightly in its bibliography handling.
    \item The unit tests are now run by \pkg{tinytest} (Dirk in \ghpr{24}).
  }
}

\section{Changes in version 0.3.6 (2018-06-10)}{
  \itemize{
    \item The vignette was updated to accomodate pandoc 2* [CRAN request].
  }
}

\section{Changes in version 0.3.5 (2018-05-19)}{
  \itemize{
    \item Update package manual page using references to
    \code{DESCRIPTION} file [CRAN request].
  }
}

\section{Changes in version 0.3.4 (2018-05-06)}{
  \itemize{
    \item Windows builds were updated (Jeroen Ooms in \ghpr{16}).
    \item Remove dynamic exception specifications which are deprecated
    with C++11 or later (Dirk in \ghpr{17}).
    \item Accomodate Solaris by being more explicit about \code{sqrt}.
  }
}

\section{Changes in version 0.3.3 (2017-09-24)}{
  \itemize{
    \item We also check for \code{gsl-config} at package load.
    \item The vignette now uses the pinp package in two-column mode.
    \item Minor other fixes to package and testing infrastructure.
  }
}

\section{Changes in version 0.3.2 (2017-03-04)}{
  \itemize{
    \item In the \code{fastLm} function, \code{.Call} now uses the
    correct \code{PACKAGE=} argument 
    \item Added file \code{init.c} with calls to \code{R_registerRoutines()}
    \code{and R_useDynamicSymbols()}; also use \code{.registration=TRUE}
    in \code{useDynLib} in \code{NAMESPACE}
    \item The skeleton configuration for created packages was updated.
  }
}
\section{Changes in version 0.3.1 (2016-10-02)}{
  \itemize{
    \item The unit test driver was updated and simplified, (by request
    of CRAN) no longer leaves files in `/tmp`, and removes two
    unexported (and unused) test helper functions (PR \ghpr{10})
    \item Switched to \code{run.sh} for Travis (PR \ghpr{11})
    \item Use canonical CRAN URLs in README.md
    \item Restored 'boxed' display of code in vignette (PR \ghpr{12})
  }
}

\section{Changes in version 0.3.0 (2015-08-30)}{
  \itemize{
    \item The RcppGSL matrix and vector class now keep track of object
      allocation and can therefore automatically free allocated object in
      the destructor. Explicit \code{x.free()} use is still supported.
    \item The matrix and vector classes now support const reference
      semantics in the interfaces (thanks to PR #7 by Dan Dillon)
    \item The matrix_view and vector_view classes are reorganized to
      better support const arguments (thanks to PR #8 and #9 by Dan Dillon)
    \item Shorthand forms such as \code{Rcpp::Matrix} have been added for
      \code{double} and \code{int} vectors and matrices including views.
    \item Examples such as \code{fastLm} can now be written in a much
      cleaner and shorter way as GSL objects can appear in the function
      signature and without requiring explicit \code{.free()} calls at the
      end.
    \item The included examples, as well as the introductory vignette,
      have been updated accordingly. 
  }
}

\section{Changes in version 0.2.5 (2015-07-05)}{
  \itemize{
    \item The \code{colnorm} function in the included example package
    was rewritten to use Rcpp Attributes, the example package was
    updated and its version number increased to 0.0.3.
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
