#!/usr/bin/r -t
#
# Copyright (C) 2010         Romain Francois and Dirk Eddelbuettel
# Copyright (C) 2014 - 2021  Dirk Eddelbuettel
#
# This file is part of RcppGSL.
#
# RcppGSL is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 2 of the License, or
# (at your option) any later version.
#
# RcppGSL is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with RcppGSL.  If not, see <http://www.gnu.org/licenses/>.

## On Windows we skip this test. We could add tools/winlibs.R and adjust
## src/Makevars.win accordingly but it might not be worth it
isWindows <- Sys.info()[["sysname"]] == "Windows"
missingEnvVar <- Sys.getenv("LIB_GSL") == ""
if (isWindows && missingEnvVar) exit_file("Skip client package test on Windows without LIB_GSL")

#test.client.package <- function(){
pkg <- "RcppGSLExample"
cwd <- getwd()
td <- tempfile()
dir.create(td)
file.copy(system.file("examples", pkg, package = "RcppGSL"), td, recursive = TRUE)
Sys.chmod(file.path(td, "RcppGSLExample", "configure"), "0755")
setwd(td)
R <- file.path(R.home(component = "bin" ), "R")
cmd <- paste("CMD build", pkg)
system2(R, cmd, stdout=FALSE, stderr=FALSE)
dir.create("templib")
cmd <- paste("CMD INSTALL -l templib", paste0(pkg, "_0.0.3.tar.gz"))
system2(R, cmd, stdout=FALSE, stderr=FALSE)
suppressMessages({
    require(Rcpp)
    require(pkg, "templib", character.only = TRUE)
})

m <- matrix(1:16, nc = 4)
res <- colNorm(m)
val <- apply(m, 2, function(x) sqrt(sum(x^2)))

expect_equal(res, val, info = "colNorm in client package")

unlink("templib", recursive = TRUE)
setwd(cwd)
unlink(td, recursive = TRUE)
