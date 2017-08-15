#ifndef STONE_H
#define STONE_H

#include "Thing.h"

class Stone : public Thing {
	
public:
	Stone(const SpatialVector& pos, const SpatialVector& vel);
	
};

#endif
