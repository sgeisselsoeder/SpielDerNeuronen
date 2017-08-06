#ifndef INTELSHEEP_H
#define INTELSHEEP_H

#include "Thing.h"

// ANA: intelsheep moves with constant speed
// ANA: the AI steers the rotation angle only
// ANA: health cannot diminish to zero; intelsheep is immortal
// ANA: Consuming berries happens automatically when intelsheep approaches a berry close enough

class IntelSheep : public Thing {
	
	double m_speed;					// constant
	double m_eatingRange;			// eats berries automatically within this range
	double m_perceptionRange;		// perception range
	double m_healthConsumption;		// diminishes while moving
	
	std::list<Thing*> thingsInSight;
	
	void perceive(World* world);
	void move(double dt);
	
public:
	IntelSheep(const SpatialVector& pos, const SpatialVector& vel);
	void progress(double dt, World* world);
	
	
};

#endif

