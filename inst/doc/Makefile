
## There is an old bug in texidvi that makes it not swallow the ~
## marker used to denote whitespace. This is actually due to fixing
## another bug whereby you could not run texidvi on directory names
## containing a tilde (as we happen to do for Debian builds of R
## alpha/beta/rc releases). The 'tilde' bug will go away as it
## reportedly has been squashed upstream but I am still bitten by it
## on Ubuntu so for now Dirk will insist on pdflatex and this helps.
whoami=$(shell whoami)

all: RcppGSL-unitTests.pdf RcppGSL.pdf

clean:
	rm -f RcppGSL.Rnw 
	cp RcppGSL/RcppGSL-fake.Rnw RcppGSL.Rnw

setvars:
ifeq (${R_HOME},)
R_HOME=	$(shell R RHOME)
endif
RPROG=	$(R_HOME)/bin/R
RSCRIPT=$(R_HOME)/bin/Rscript

RcppGSL-unitTests.pdf:
	rm -fr unitTests-results/*
	$(RSCRIPT) --vanilla unitTests/RcppGSL-unitTests.R
	$(RPROG) CMD Sweave RcppGSL-unitTests.Rnw
	$(RSCRIPT) --vanilla -e "tools::texi2dvi( 'RcppGSL-unitTests.tex', pdf = TRUE, clean = TRUE )"
	rm -fr RcppGSL-unitTests.tex

RcppGSL.pdf: RcppGSL/RcppGSL.Rnw
	cp -f RcppGSL/RcppGSL.Rnw .
	$(RSCRIPT) --vanilla -e "require(highlight); driver <- HighlightWeaveLatex(boxes = TRUE); Sweave( 'RcppGSL.Rnw', driver = driver ); "
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL
else
	$(RSCRIPT) -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = FALSE )"
endif
	bibtex RcppGSL
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL
	pdflatex RcppGSL
else
	$(RSCRIPT) -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = TRUE )"
endif
	rm -fr RcppGSL.tex RcppGSL.bbl RcppGSL.blg RcppGSL.aux RcppGSL.out RcppGSL.log 
	cp RcppGSL/RcppGSL-fake.Rnw RcppGSL.Rnw
