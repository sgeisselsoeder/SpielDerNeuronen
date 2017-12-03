#include "Stone.h"

Stone::Stone(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
	
	m_friction				= 1.0;
	m_mass					= 1000.0;
	m_health				= 10.0;
	
	m_classID				= 3;
	
}
