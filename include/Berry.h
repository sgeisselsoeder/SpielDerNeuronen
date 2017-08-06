#ifndef BERRY_H
#define BERRY_H

#include "Thing.h"

class Berry : public Thing {
	
public:
	double transferHealth(const Thing* healthSucker);
	Berry(const SpatialVector& pos, const SpatialVector& vel);
	
	
};

#endif
