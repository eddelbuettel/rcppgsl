
sources :=              $(wildcard *.Rmd)
vignettes :=            $(sources:.Rmd=.pdf)

all:                    ${vignettes}

%.pdf:                  %.Rmd
			Rscript -e 'rmarkdown::render("$^")'
			Rscript -e 'tools::compactPDF("$@")'
			mv -v $@ ..

clean:
			rm -f pinp.cls jss.bst RcppGSL*.tex
