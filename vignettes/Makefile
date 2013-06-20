
## There is an old bug in texidvi that makes it not swallow the ~
## marker used to denote whitespace. This is actually due to fixing
## another bug whereby you could not run texidvi on directory names
## containing a tilde (as we happen to do for Debian builds of R
## alpha/beta/rc releases). The 'tilde' bug will go away as it
## reportedly has been squashed upstream but I am still bitten by it
## on Ubuntu so for now Dirk will insist on pdflatex and this helps.
whoami=$(shell whoami)

all: RcppGSL-unitTests.pdf RcppGSL-intro.pdf

clean:	
	rm -f RcppGSL*.log RcppGSL*.aux RcppGSL*.out RcppGSL*.tex *.blg *.bbl *~
	rm -rf auto/

pdfclean:
	rm -f RcppGSL-unitTests.pdf RcppGSL-intro.pdf

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

RcppGSL-intro.pdf: RcppGSL/RcppGSL-intro.Rnw
	cp -f RcppGSL/RcppGSL-intro.Rnw .
	$(RSCRIPT) --vanilla -e "require(highlight); driver <- HighlightWeaveLatex(boxes = TRUE); Sweave( 'RcppGSL-intro.Rnw', driver = driver ); "
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL-intro
else
	$(RSCRIPT) -e "tools::texi2dvi( 'RcppGSL-intro.tex', pdf = TRUE, clean = FALSE )"
endif
	bibtex RcppGSL-intro
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL-intro
	pdflatex RcppGSL-intro
else
	$(RSCRIPT) -e "tools::texi2dvi( 'RcppGSL-intro.tex', pdf = TRUE, clean = TRUE )"
endif
	rm -fr RcppGSL-intro.tex RcppGSL-intro.bbl RcppGSL-intro.blg RcppGSL-intro.aux RcppGSL-intro.out RcppGSL-intro.log 
	cp RcppGSL/RcppGSL-fake.Rnw RcppGSL-intro.Rnw
