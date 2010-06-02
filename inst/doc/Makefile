
all: clean RcppGSL.pdf

clean:
	touch RcppGSL.pdf
	rm RcppGSL.pdf

RcppGSL.pdf: RcppGSL/RcppGSL.Rnw
	rm RcppGSL.Rnw 
	cp -f RcppGSL/RcppGSL.Rnw .
	Rscript -e "require(highlight); driver <- HighlightWeaveLatex(boxes = TRUE, bg = 'white' ); Sweave( 'RcppGSL.Rnw', driver = driver ); "
	Rscript -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = FALSE )"
	bibtex RcppGSL
	Rscript -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = TRUE )"
	# rm -fr RcppGSL.tex
	rm -fr RcppGSL.bbl
	rm -fr RcppGSL.blg
	rm -fr RcppGSL.aux
	rm -fr RcppGSL.out
	rm -fr RcppGSL.log
	rm RcppGSL.Rnw
	cp RcppGSL/RcppGSL-fake.Rnw RcppGSL.Rnw
	
	
