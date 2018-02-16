CXX=g++
CXXFLAGS= -g -O3
EXEC=maxc
SRC=maxc.cpp
default:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)
	pdflatex report.tex
	mkdir edgls adjmat outclq
report:
	pdflatex report.tex
