#!/usr/bin/r -t
#                        Emacs make this -*- mode: R; tab-width: 4 -*-
#
# Copyright (C) 2010 - 2019	 Romain Francois and Dirk Eddelbuettel
# Copyright (C) 2016         Dirk Eddelbuettel
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

library(RcppGSL)

#test.fastLm <- function() {
data(trees, package="datasets")
flm <- fastLmPure(cbind(1, log(trees$Girth)), log(trees$Volume))
fit <- lm(log(Volume) ~ log(Girth), data=trees)

expect_equal(as.numeric(flm$coef), as.numeric(coef(fit)), info="fastLm.coef")
expect_equal(as.numeric(flm$stderr), as.numeric(coef(summary(fit))[,2]), info="fastLm.stderr")
expect_equal(as.numeric(flm$df.residual), as.numeric(fit$df.residual), info="fastLm.df.residual")

#test.fastLm.default <- function() {
data(trees, package="datasets")
flm <- RcppGSL:::fastLm.default(cbind(1, log(trees$Girth)), log(trees$Volume))
fit <- lm(log(Volume) ~ log(Girth), data=trees)

expect_equal(as.numeric(flm$coefficients), as.numeric(coef(fit)), info="fastLm.default.coef")
expect_equal(as.numeric(flm$stderr), as.numeric(coef(summary(fit))[,2]), info="fastLm.default.stderr")
expect_equal(as.numeric(flm$df.residual), as.numeric(fit$df.residual), info="fastLm.default.df.residual")
expect_equal(as.numeric(flm$residuals), as.numeric(fit$residuals), info="fastLm.default.residuals")
expect_equal(as.numeric(flm$fitted.values), as.numeric(fit$fitted.values), info="fastLm.default.fitted.values")

#test.summary.fastLm <- function() {
data(trees, package="datasets")
sflm <- summary(fastLm(log(Volume) ~ log(Girth), data=trees))
sfit <- summary(lm(log(Volume) ~ log(Girth), data=trees))

expect_equal(as.numeric(coef(sflm)), as.numeric(coef(sfit)), info="summary.fastLm.coef")
expect_equal(sflm$r.squared, sfit$r.squared, info="summary.fastLm.r.squared")
expect_equal(sflm$adj.r.squared, sfit$adj.r.squared, info="summary.fastLm.r.squared")
expect_equal(sflm$sigma, sfit$sigma, info="summary.fastLm.sigma")

## no intercept case
sflm <- summary(fastLm(log(Volume) ~ log(Girth) - 1, data=trees))
sfit <- summary(lm(log(Volume) ~ log(Girth) - 1, data=trees))
expect_equal(as.numeric(coef(sflm)), as.numeric(coef(sfit)), info="summary.fastLm.coef.noint")
expect_equal(sflm$r.squared, sfit$r.squared, info="summary.fastLm.r.squared.noint")
expect_equal(sflm$adj.r.squared, sfit$adj.r.squared, info="summary.fastLm.r.squared.noint")
expect_equal(sflm$sigma, sfit$sigma, info="summary.fastLm.sigma.noint")

## non-formula use
sflm <- summary(fastLm(log(trees$Girth), log(trees$Volume)))
sfit <- summary(lm(log(Volume) ~ log(Girth) - 1, data=trees))
expect_equal(as.numeric(coef(sflm)), as.numeric(coef(sfit)), info="summary.fastLm.coef.nonform")
expect_equal(sflm$r.squared, sfit$r.squared, info="summary.fastLm.r.squared.nonform")
expect_equal(sflm$adj.r.squared, sfit$adj.r.squared, info="summary.fastLm.r.squared.nonform")
expect_equal(sflm$sigma, sfit$sigma, info="summary.fastLm.sigma.nonform")

#test.fastLm.formula <- function() {
data(trees, package="datasets")
flm <- fastLm(log(Volume) ~ log(Girth), data=trees)
fit <- lm(log(Volume) ~ log(Girth), data=trees)

expect_equal(flm$coefficients, coef(fit), info="fastLm.formula.coef")
expect_equal(as.numeric(flm$stderr), as.numeric(coef(summary(fit))[,2]), info="fastLm.formula.stderr")
expect_equal(as.numeric(flm$df.residual), as.numeric(fit$df.residual), info="fastLm.formula.df.residual")
expect_equal(as.numeric(flm$residuals), as.numeric(fit$residuals), info="fastLm.formula.residuals")
expect_equal(as.numeric(flm$fitted.values), as.numeric(fit$fitted.values), info="fastLm.formula.fitted.values")
