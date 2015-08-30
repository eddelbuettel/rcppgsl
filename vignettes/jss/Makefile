article=jss-submission
all: clean ${article}.pdf

${article}.pdf: ${article}.Rnw
#	R CMD Sweave ${article}.Rnw
#	Rscript -e 'Sweave("jss-submission.Rnw", driver=highlight::HighlightWeaveLatex(boxes=TRUE))'
	Rscript -e 'Sweave("jss-submission.Rnw", driver=highlight::HighlightWeaveLatex())'
#	Rscript -e 'tools::texi2pdf("jss-submission.Rnw")'
	pdflatex ${article}.tex
	bibtex ${article}
	pdflatex ${article}.tex
	pdflatex ${article}.tex
	R CMD Stangle ${article}.Rnw

jssarchive:
	(cd .. && zip -r jss-submission_$$(date "+%Y-%m-%d").zip jss/ -x "jss/JSSstyle/*" -x "jss/JSSemails/*")

clean:
	rm -fr ${article}.out ${article}.aux ${article}.log ${article}.bbl \
	  ${article}.blg ${article}.brf figures/fig-???.pdf

