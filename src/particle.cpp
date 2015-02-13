#include "particle.h"
#include "constants.h"
#include <vector>

Particle::Particle() {
	pos = {-1.,-1.,-1};
}

Particle::Particle(const std::vector<double>& p) {
	pos = p;
}

Particle::Particle(const Particle& p) {
	pos = p.pos;
}

Particle& Particle::operator=(const Particle& p) {
	pos = p.pos;
	return *this;
}

