#ifndef PARTICLE
#define PARTICLE

#include <vector>

class Particle {
	public:
		Particle();
		Particle(const std::vector<double>& p);
		Particle(const Particle& p);
		Particle& operator=(const Particle&);
		std::vector<double> pos;
	private:
		void applyBorderConditions();
};

#endif //PARTICLE
