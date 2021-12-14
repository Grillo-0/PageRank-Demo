CXXFLAGS=-O2 -larmadillo

page-rank: src/page-rank.cpp
	${CXX} ${CXXFLAGS} src/page-rank.cpp -o page-rank.out

clean:
	rm page-rank
