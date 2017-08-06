#ifndef BERRY_H
#define BERRY_H

#include "Thing.h"

class Berry : public Thing {
	
public:
	double giveUpHealth(const Thing* healthSucker);
	Berry(const SpatialVector& pos, const SpatialVector& vel);
	
	
};

#endif
