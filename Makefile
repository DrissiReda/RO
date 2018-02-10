default:
	g++ -g clique.cpp -o clique
	pdflatex Report/rapport.tex
conv:
	g++ -g edgtoadj.cpp -o edgtoadj

