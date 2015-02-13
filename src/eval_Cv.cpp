#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include "constants.h"
//evaluate Cv using the variance of energy

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

	std::vector<double> allData;
	double tmp = 0.;
	unsigned int count = 0, cutAt = 10000;
	while(in >> tmp) {
		if(count >= cutAt)
			allData.push_back(tmp);
		++count;
	}
	unsigned int allDataN = allData.size();
	
	for(unsigned int step = 1; step < 3000; ++step) {
		//fill array with data every 'step' steps
		std::vector<double> data;
		for(unsigned int i=0; i<allDataN/step; ++i)
			data.push_back(allData[i*step]);
			
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
	
		std::cout << step << " " << Cv << std::endl;
	}

	return 0;
}
