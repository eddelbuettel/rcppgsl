#!/usr/bin/r -t
#                        Emacs make this -*- mode: R; tab-width: 4 -*-
#
# Copyright (C) 2010 - 2011	 Romain Francois and Dirk Eddelbuettel
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

test.fastLm <- function() {
    data(trees)
    flm <- .Call("fastLm",
                 cbind(1, log(trees$Girth)),
                 log(trees$Volume),
                 PACKAGE="RcppGSL")
    fit <- lm(log(Volume) ~ log(Girth), data=trees)

    checkEquals( as.numeric(flm$coef), as.numeric(coef(fit)),
                msg="fastLm.coef")
    checkEquals( as.numeric(flm$stderr), as.numeric(coef(summary(fit))[,2]),
                msg="fastLm.stderr")
}

test.fastLm.formula <- function() {
    data(trees)
    flm <- fastLm(log(Volume) ~ log(Girth), data=trees)
    fit <- lm(log(Volume) ~ log(Girth), data=trees)

    checkEquals(flm$coefficients, coef(fit), msg="fastLm.formula.coef")
    checkEquals(as.numeric(flm$stderr), as.numeric(coef(summary(fit))[,2]),
                msg="fastLm.formula.stderr")
}




