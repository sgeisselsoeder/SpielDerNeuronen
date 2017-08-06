#include "Berry.h"

double Berry::transferHealth(const Thing* healthSucker) {
	
	double health = m_health;
	m_health = 0.0;
	return health;
	
}

Berry::Berry(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
	
	m_friction				= 1.0;
	m_mass					= 1.0;
	m_health				= 10.0;
	
	classID					= "Berry";
	
}
