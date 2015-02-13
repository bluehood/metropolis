#ifndef CONSTANTS
#define CONSTANTS

#include <cmath>

static const unsigned int N = 100;
static const double density = 0.5,
	boxSize = pow(N/density,1./3.),
	boxTemp = 2.,
	cutOff = boxSize/2.,
	delta = boxSize/12.;
//	delta = boxSize/12.; //about 0.5
	
#endif //CONSTANTS
