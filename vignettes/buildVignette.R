#!/usr/bin/Rscript

args <- commandArgs(TRUE)
if (length(args) == 0) {
    cat("No argument given, using 'RcppGSL-intro.Rnw'\n")
    srcfile <- "RcppGSL-intro.Rnw"
} else {
    srcfile <- args[1]
}

texfile <- gsub(".Rnw", ".tex", srcfile)

Sweave(srcfile, driver=highlight::HighlightWeaveLatex())
tools::texi2pdf(texfile)

