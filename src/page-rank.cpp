#include <iostream>
#include <armadillo>


arma::sp_mat generateLinkMatrix(std::size_t nNodes, std::size_t maxEdgesPerNode) {

	arma::sp_mat linkMatrix{nNodes, nNodes};
	for(int i=0; i<nNodes ; ++i){
		std::size_t nLinks = rand() % maxEdgesPerNode;

		std::vector<std::size_t> pos;
		for(int j=0; j<nNodes; ++j){
			pos.push_back(j);
		}
		pos.erase(std::begin(pos) + i);
		
		for(int j=0; j<nLinks; ++j){
			std::size_t index = rand() % pos.size();
			linkMatrix(pos[index],i) = 1/static_cast<double>(nLinks); 
			pos.erase(std::begin(pos)+index);
		}
	}

	return linkMatrix;
};

arma::vec rankSites(const arma::sp_mat& linkMatrix, const float& p) {

	arma::vec v = arma::ones<arma::vec>(linkMatrix.n_cols);
	double epsilon = 10e-10;
	while (true) {
		auto previous = v;
		v = (p/linkMatrix.n_cols) * v + (1-p) * (linkMatrix * v);
		if (all((v-previous) < epsilon)){
			break;
		}
	}	

	return v;
}

double lerp(const double& value, 
			const double& minIn, double maxIn, 
			const double& minOut, const double& maxOut) {
	return minOut + (value + minIn) * (maxOut - minOut)/(maxIn - minIn);

}
void makeGraph(const arma::sp_mat& linkMatrix, const arma::vec& rank) {
	using namespace arma;

	std::cout << "digraph {" << std::endl;
	std::cout << "\tnode [style=\"filled\"]" << std::endl;
	for(int i=0; i< linkMatrix.n_cols; ++i) {
		sp_mat::const_iterator it     = linkMatrix.begin_col(i);
		sp_mat::const_iterator it_end = linkMatrix.end_col(i);
		std::cout << "\t" << i << " ["; 
		std::cout << "fontsize=" << "\""<< lerp(rank[i], rank.min(), rank.max(), 10, 300)<< "pt\"";
		if(rank[i] == rank.max()) 
			std::cout << " fillcolor=" << "\"green\"";
		std::cout << "]" << std::endl;
		for(; it != it_end; ++it) {
			std::cout << "\t" << i << "->" << it.row() << std::endl;
		}
	}
	std::cout << "}" << std::endl;
}

int main(int argc, char* argv[]) {
	srand (time(NULL));
	arma::sp_mat A = generateLinkMatrix(atoi(argv[1]), atoi(argv[2]));

	arma::vec v = rankSites(A, atof(argv[3]));

	makeGraph(A,v);
}
