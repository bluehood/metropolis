#include "metropolis.h"
#include "particle.h"
#include "constants.h"
#include <vector>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>

Metropolis::Metropolis(const std::vector<Particle>& p) : particles(p), pNum(p.size()), 
		dim(particles[0].pos.size()), randDouble(0.0,1.0), randInt(0,p.size()-1), gen(1) {
	updateTotEnergy();
	acceptance = 0.;
}

double Metropolis::getEnergy() const {
	return U;
}

double Metropolis::getAcceptance() const {
	return acceptance;
}

void Metropolis::makeMove() {
	//choose random particle to move
	unsigned int pInd = randInt(gen);
	//choose new position at random
	const std::vector<double>& oldPos = particles[pInd].pos;
	std::vector<double> newPos(dim);
	for(unsigned int i=0; i<dim; ++i)
		newPos[i] = oldPos[i] + delta*(randDouble(gen) - 0.5);
	//evaluate acceptance
	double deltaU = evalEnergy(pInd,newPos) - evalEnergy(pInd);
	static unsigned int acceptedMoves = 0;
	static unsigned int totalMoves = 0;
	if(randDouble(gen) < exp(-deltaU/boxTemp)) {
		//accept move	
		particles[pInd].pos = applyBorderConditions(newPos);
		if(acceptedMoves % 100000 != 0)
			U += deltaU;
		else {
			updateTotEnergy();
		}
		++acceptedMoves;
		++totalMoves;
	}
	else {
		++totalMoves;
	}
	acceptance = double(acceptedMoves)/totalMoves;
}

double Metropolis::evalEnergy(const unsigned int pInd, const std::vector<double>& altPos) const {
	double u = 0.;
	std::vector<double> pos;
	if(!altPos.empty())
		pos = altPos;
	else
		pos = particles[pInd].pos;

	for(unsigned int i=0; i<pNum; ++i) {
		if(i != pInd)
			u += lennardJones(minD2fast(pos,particles[i].pos));
	}
	return u;
}

void Metropolis::updateTotEnergy() {
	double newU = 0.;
	for(unsigned int i=0; i<pNum; ++i)
		newU += evalEnergy(i);
	U = newU/2.;
}

double d2(const std::vector<double>& p1, const std::vector<double>& p2) {
	double d2 = 0.;
	const unsigned int dim = p1.size();
	for(unsigned int i=0; i<dim; ++i)
		d2 += (p1[i] - p2[i])*(p1[i] - p2[i]);
	return d2;
}

double Metropolis::minD2fast(const std::vector<double>& fixPos, const std::vector<double>& testPos) const {
	double minD2 = 0.;
	for(unsigned int i=0; i<dim; ++i) {
		double dist = testPos[i] - fixPos[i];
		if(dist > cutOff)
			dist -= boxSize;
		else if(dist < -cutOff)
			dist += boxSize;
		minD2 += dist*dist;
	}
	return minD2;
}

double Metropolis::minD2(const std::vector<double>& fixPos, const std::vector<double>& testPos) const {
	double minD2 = boxSize*100;
	for(int horiz = -1; horiz <= 1; ++horiz)
		for(int vert = -1; vert <= 1; ++vert)
			for(int front = -1; front <= 1; ++front) {
				std::vector<double> tmpPos = testPos;
				tmpPos[0] += boxSize*horiz;
				tmpPos[1] += boxSize*vert;
				tmpPos[2] += boxSize*front;
				double dNew2 = d2(fixPos,tmpPos);
				if(minD2 > dNew2)
					minD2 = dNew2;
				if(minD2 < cutOff*cutOff)
					goto exitPoint;
			}
	exitPoint: ;
	return minD2;
}

double Metropolis::lennardJones(const double d2) const {
	if(d2 > cutOff*cutOff)
		return 0.;
	return 4*(1./pow(d2,6) - 1./pow(d2,3));
}

std::vector<double> Metropolis::applyBorderConditions(std::vector<double>& pos) {
	for(unsigned int i=0; i<dim; ++i) {
		while(pos[i] > boxSize)
			pos[i] -= boxSize;
		while(pos[i] < 0)
			pos[i] += boxSize;
	}
	return pos;
}
