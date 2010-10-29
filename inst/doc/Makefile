
## There is an old bug in texidvi that makes it not swallow the ~
## marker used to denote whitespace. This is actually due to fixing
## another bug they whereby you could not run texidvi on directory
## names containing a tilde (as we happen to do for Debian builds of R
## alpha/beta/rc releases). The 'tilde' bug will go away as it
## reportedly has been squashed upstream but I am still bitten by it
## on Ubuntu so for Dirk will insist on pdflatex and this variable helps
whoami=$(shell whoami)

all: clean RcppGSL.pdf

clean:
        # rm RcppGSL.pdf

RcppGSL.pdf: RcppGSL/RcppGSL.Rnw
	cp -f RcppGSL/RcppGSL.Rnw .
	Rscript -e "require(highlight); driver <- HighlightWeaveLatex(boxes = TRUE, bg = 'white' ); Sweave( 'RcppGSL.Rnw', driver = driver ); "
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL
else
	Rscript -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = FALSE )"
endif
	bibtex RcppGSL
ifneq (,$(findstring edd,$(whoami)))
	pdflatex RcppGSL
else
	Rscript -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = TRUE )"
endif
        # rm -fr RcppGSL.tex
	rm -fr RcppGSL.bbl RcppGSL.blg RcppGSL.aux RcppGSL.out RcppGSL.log rm RcppGSL.Rnw
	cp RcppGSL/RcppGSL-fake.Rnw RcppGSL.Rnw
