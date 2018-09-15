#ifndef INTELSHEEP_H
#define INTELSHEEP_H

#include "Thing.h"
#include <iostream>
#include <fstream>


// ANA: intelsheep moves with constant speed
// ANA: the AI steers the rotation angle only
// ANA: health cannot diminish to zero; intelsheep is immortal
// ANA: Consuming berries happens automatically when intelsheep approaches a berry close enough

class IntelSheep : public Thing {
	
	double m_speed;					// constant
	double m_eatingRange;			// eats berries automatically within this range
	double m_perceptionRange;		// perception range
	double m_perceptionAngle;		// perception angle
	double m_healthConsumption;		// diminishes while moving
	double m_healthOld;				// health at previous timestep
	std::ofstream m_log;
	
	std::list<ThingPtr> m_thingsInSight;
	
	void perceive(World* world);
	void logPerception();
	void logStatus();
	void comeUpWithPlan();
	void move(double dt, World* world);
	
public:

	IntelSheep(const SpatialVector& pos, const SpatialVector& vel);
	~IntelSheep();
	void progress(double dt, World* world);
	
	double transferHealth(const Thing* healthSucker);
	
};

#endif


