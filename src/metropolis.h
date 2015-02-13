#ifndef METRO
#define METRO

#include "particle.h"
#include <vector>
#include <random>

class Metropolis {
	public:
	Metropolis(const std::vector<Particle>& p);
	
	double getEnergy() const;
	double getAcceptance() const;
	void makeMove();

	private:
	//evaluate interaction energy of particle pInd and all other particles
	//if pos is not empty, use those coordinates instead of pInd's
	double evalEnergy(const unsigned int pInd, const std::vector<double>& altPos = std::vector<double>()) const;
	//evaluate total energy (use with caution)
	void updateTotEnergy();
	double minD2fast(const std::vector<double>& fixPos, const std::vector<double>& testPos) const;
	double minD2(const std::vector<double>& fixPos, const std::vector<double>& testPos) const;
	double lennardJones(const double d2) const;
	std::vector<double> applyBorderConditions(std::vector<double>& pos);
	
	std::vector<Particle> particles;
	const unsigned int pNum, dim;
	double U, acceptance;
	std::mt19937 gen;
	std::uniform_real_distribution<double> randDouble;
	std::uniform_int_distribution<int> randInt;
};

#endif //METRO
