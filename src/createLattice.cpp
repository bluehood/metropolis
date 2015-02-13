#include <fstream>
#include <iostream>
#include <cmath>
#include "constants.h"

int main() {
	std::ofstream out("input.txt");
	double step = 0.9*boxSize/pow(N,1./3.);
	for(unsigned int i=0; i<5; ++i) {
		for(unsigned int j=0; j<5; ++j) {
			for(unsigned int z=0; z<4; ++z) {
				out << i*step << " " << j*step << " " << z*step << std::endl;
			}
		}
	}
	return 0;
}
