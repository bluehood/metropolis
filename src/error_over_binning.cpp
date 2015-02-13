#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << "Usage " << argv[0] << " <data file>" << std::endl;
		return 1;
	}
	
	std::ifstream in(argv[1]);
	double tmp;
	unsigned int count = 0, cutAt = 5000;
	std::vector<double> data;
	while(in >> tmp) {
		if(count >= cutAt)
			data.push_back(tmp);
		++count;
	}
	unsigned int n = data.size();

	std::string file = "corr_over_lbin.txt";
	std::ofstream out(file);
	for(unsigned int b = 10; b<50000; b+=200) {
		unsigned int nBins = n/b; 
		double bins[nBins];
		for(unsigned int i=0; i<nBins; ++i)
			bins[i] = 0;
		double avg = 0., var = 0.;
		for(unsigned int i=0; i<nBins; ++i) {
			for(unsigned int j=0; j<b; ++j)
				bins[i] += data[i*b + j];
			bins[i] /= b;
			avg += bins[i];
			var += bins[i]*bins[i];
		}
		avg /= nBins;
		var = var/nBins - avg*avg;
		out << b << " " << sqrt(var/nBins) << std::endl;
	}
	std::cout << "output written on file \'" << file << "\'" << std::endl;
	
	return 0;
}
