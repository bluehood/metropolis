#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include "constants.h"

int main(int argc, char** argv) {
	if(argc<2) {
		std::cerr << "Usage: " << argv[0] << " <data file>\n";
		return 1;
	}
	std::ifstream in(argv[1]);
	if(!in) {
		std::cerr << "Error: could not open file \'" << argv[1] << "\' for reading\n";
		return 2;
	}

	std::vector<double> data;
	double tmp, binSum = 0.;
	unsigned int countCut = 0, cutAt = 5000, countBin = 0, binning = 5000;
	while(in >> tmp) {
		if(countCut >= cutAt) {
			binSum += tmp;
			++countBin;
			if(countBin%binning == 0) {
				data.push_back(binSum/binning);
				binSum = 0.;
			}
		}
		++countCut;
	}
	
	//evaluate average, variance and std deviation
	const unsigned int n = data.size();
	double avg = 0., var = 0.;
	for(double x : data) {
		avg += x;
		var += x*x;
	}
	avg /= n;
	var = var/n - avg*avg;
	double Cv = var / (boxTemp*boxTemp);

	std::cout << "avg " << avg << "\nvar " << var << "\nstddev " << sqrt(var) << std::endl;
	std::cout << "Cv " << Cv << "\nstddev of mean " << sqrt(var/data.size()) << std::endl;

	return 0;
}
