CXX=g++
OPTS= -DVERBOSE
CXXFLAGS= -g
EXEC=clique
SRC=clique.cpp
default:
	#@mkdir edgls adjmat outclq
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)
	pdflatex Report/rapport.tex
verbose:
	#@mkdir edgls adjmat outclq
	$(CXX) $(CXXFLAGS) $(OPTS) $(SRC) -o $(EXEC)
	pdflatex Report/rapport.tex
conv:
	$(CXX) edgtoadj.cpp -o edgtoadj
