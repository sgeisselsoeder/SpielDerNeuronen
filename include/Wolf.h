#ifndef WOLF_H
#define WOLF_H

#include "Thing.h"
#include <iostream>
#include <fstream>


class Wolf : public Thing {
	
	double m_speed;					// constant
	double m_eatingRange;			// eats automatically within this range
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

	Wolf(const SpatialVector& pos, const SpatialVector& vel);
	~Wolf();
	void progress(double dt, World* world);
	
};

#endif


