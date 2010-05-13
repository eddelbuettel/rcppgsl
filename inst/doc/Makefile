
all: clean index.html RcppGSL.pdf

clean:
	touch RcppGSL.pdf
	rm RcppGSL.pdf

RcppGSL.pdf:
	R CMD Sweave RcppGSL.Rnw
	Rscript -e "tools::texi2dvi( 'RcppGSL.tex', pdf = TRUE, clean = TRUE )"
	rm -fr RcppGSL.tex

