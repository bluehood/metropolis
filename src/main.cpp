#include "particle.h"
#include "metropolis.h"
#include "constants.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <energy file> [n moves]\n";
		return 1;
	}
	std::ofstream outEnergy(argv[1]);
	if(!outEnergy) {
		std::cerr << "Error: could not open file \'" << argv[1] << "\' for writing\n";
		return 2;
	}
	
	std::string inFile = "lattice.txt";
	std::ifstream input(inFile);
	if(!input) {
		std::cerr << "Error: could not open file \'" << inFile << "\' for reading";
		return 3;
	}

	unsigned int nMoves = 0;
	if(argc >= 3) {
		std::stringstream str(argv[2]);
		str >> nMoves;
	}
	else
		nMoves = 100000;

	//fill lattice
	std::vector<Particle> particles;
	std::string line;
	while(getline(input,line)) {
		std::stringstream str(line);
		double coord;
		std::vector<double> pos;
		while(str >> coord)
			pos.push_back(coord);
		particles.push_back(Particle(pos));
	}

	Metropolis m(particles);
	std::cout << m.getEnergy() << std::endl;
	//make your moves
	for(unsigned int i=0; i<nMoves; ++i) {
		m.makeMove();
		outEnergy << m.getEnergy() << std::endl;
	}

	return 0;
}
