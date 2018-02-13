CXX=g++
OPTS= -DVERBOSE
CXXFLAGS= -g -O3
EXEC=clique
SRC=clique.cpp
default:
	#@mkdir edgls adjmat outclq
	$(CXX) $(CXXFLAGS) $(SRC) -o $(EXEC)
	$(CXX) $(CXXFLAGS) maxc.cpp -o maxc
	pdflatex Report/rapport.tex 
verbose:
	#@mkdir edgls adjmat outclq
	$(CXX) $(CXXFLAGS) $(OPTS) $(SRC) -o $(EXEC)
	pdflatex Report/rapport.tex
conv:
	$(CXX) edgtoadj.cpp -o edgtoadj
