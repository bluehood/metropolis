#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
	if(argc < 2) {
		std::cerr << "Usage: " << argv[0] << " <input file\n";
		return 1;
	}
	//read data from file
	std::ifstream in(argv[1]);
	if(!in) {
		std::cerr << "Could not open file \'" << argv[0] << "\' for reading\n";
		return 2;
	}
	double tmp;
	std::vector<double> data;
	while(in >> tmp)
		data.push_back(tmp);
	unsigned int n = data.size();

	//write correlation to file
	std::string corrFile = "corr_over_dt.txt";
	std::ofstream corrOut(corrFile);
	for(unsigned int dt = 10; dt < 20000; dt += 50) {
		//for each dt, evaluate <U(t)U(t+dt)>, <U(t)> and <U(t+dt)>
		double Ut = 0., Utdt = 0., UtUtdt = 0.;
		double stdDevUt = 0., stdDevUtdt = 0.;
		for(unsigned int i=0; i<n-dt; ++i) {
			double datai = data[i], dataidt = data[i+dt];
			Ut += datai;
			stdDevUt += datai*datai;
			Utdt += dataidt;
			stdDevUtdt += dataidt*dataidt;
			UtUtdt += datai*dataidt;
		}
		Ut /= n-dt;
		stdDevUt = stdDevUt/(n-dt) - Ut*Ut;
		Utdt /= n-dt;
		stdDevUtdt = stdDevUtdt/(n-dt) - Utdt*Utdt;
		UtUtdt /= n-dt;
		// sigmaxy / sigmax*sigmay
		corrOut << dt << " " << (UtUtdt - Ut*Utdt)/(stdDevUt*stdDevUtdt) << std::endl;
	}
	std::cout << "correlation data written in \'" << corrFile << "\'" << std::endl;
	return 0;
}
