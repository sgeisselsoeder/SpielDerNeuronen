#include "IntelSheep.h"
#include <algorithm>
#include <limits>

IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
//~ IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel, World* world) : Thing(pos, vel, world) {
	
	m_speed					= 1.0;
	m_friction				= 0.0;
	m_mass					= 100.0;
	m_eatingRange			= 1.5;
	m_perceptionRange		= 50.0;
	m_perceptionAngle		= 2.0*M_PI;
	m_healthConsumption		= 0.1;
	m_health				= 100.0;
	m_healthOld				= m_health;
	
	m_classID				= 5;
	
	m_log.open("log.txt");
}

IntelSheep::~IntelSheep(){
	m_log.close();
}

void IntelSheep::perceive(World* world) {
	//~ std::list<ThingPtr> m_thingsInSight
	
	m_thingsInSight = world->getThings(m_position, m_perceptionRange, m_velocity, m_perceptionAngle);
	//std::cout << "Number of percieved objects " << m_thingsInSight.size() << std::endl;
	
	// NOTE: maybe put filtering for closest object into getThings, add argument unsigned int numClosestObjects, 0 means all
	
	// NOTE: For now, the intelSheep is confused by more than 10 objects
	const unsigned int maxNumObjects = 10;	// SG: TODO make maxNumObjects a member variable and hence a property of the class
	if (m_thingsInSight.size() > maxNumObjects){
		// Sort all percieved things according to their distance
		std::vector<double> distances(maxNumObjects, 0.0);
		for(std::list<ThingPtr>::const_iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
			distances.push_back(((*it)->getPosition() - m_position).length());
		}
		std::sort(distances.begin(), distances.end());
		// Remember the distance of the farest object we can handle
		double threshold = distances[maxNumObjects];
		
		// Remove all perceived objects that are further away
		for(std::list<ThingPtr>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ) {
			double distance = ((*it)->getPosition() - m_position).length();
			if (distance > threshold) {
				m_thingsInSight.erase(it);
			} else {
				++it;
			}
		}
	}
	
}

// Log the perception to file
void IntelSheep::logPerception(){
	//m_log << "Perception: " << std::endl;
	// Percieve as many objects as are around
	for(std::list<ThingPtr>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
		//m_log << (*it)->getClassID() << " " << ((*it)->getPosition() - m_position) << std::endl;
		m_log << (*it)->getClassID() << " " << ((*it)->getPosition() - m_position) << " ";
	}
	const unsigned int minNumberObjects = 10;
	// Always write AT LEAST the required number of objects
	for(unsigned int i = 0; i < (minNumberObjects-m_thingsInSight.size()); ++i ) {
		//m_log << 0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
		m_log << 0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << " ";
	}
	m_log << std::endl;
	
}

// Log the status to file
void IntelSheep::logStatus(){
	/*
	m_log << "Object: " << std::endl;
	m_log << m_classID << " " << m_health << " " << m_position << " " << m_velocity << std::endl;
	*/
	m_log << m_health << " " << m_position << " " << m_velocity << " ";
}

void IntelSheep::comeUpWithPlan() {
	// ANA: AI processing here!
	
	// SG: by default: the most intelligent movement ever:
	m_velocity.randomize();
	
	// but also: check all percieved objects
	double distanceToClosestBerrySoFar = std::numeric_limits<double>::max();
	for(std::list<ThingPtr>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
		// only act on berries
		if ((*it)->getClassID() == 1) {
			// how far is it to this berry
			double distanceToThisBerry = distance(m_position, (*it)->getPosition());
			//std::cout << "Found a berry at distance " << distanceToThisBerry << " best so far: " << distanceToClosestBerrySoFar << std::endl;
			// have we seen a closer one?
			if (distanceToThisBerry < distanceToClosestBerrySoFar) {
				// we want to go to this berry! It's delicious
				distanceToClosestBerrySoFar = distanceToThisBerry;
				m_velocity = (*it)->getPosition()-m_position;
				//std::cout << " moving from " << m_position << " to " << (*it)->getPosition() << " in direction " << m_velocity << std::endl;
			}
		}
	}
	
}

void IntelSheep::progress(double dt, World* world) {
	
	// log the status
	logStatus();
	
	// Percieve objects in the world around us
	perceive(world);
	// log the percieved objects
	logPerception();
	
	// Think about what the sheep saw and determine a strategy what to do next
	comeUpWithPlan();
	
	// Move accordingly
	move(dt, world);
	
	// TODO: change this:
	// current: percieved again to eat
	// target: only check already percieved objects for deliciousness
	std::list<ThingPtr> thingsInFront = world->getThings(m_position, m_eatingRange, m_velocity, m_perceptionAngle);
	for(std::list<ThingPtr>::iterator it = thingsInFront.begin(); it != thingsInFront.end(); ++it) {
		// eat the berries (berry class ID = 1)!
		if ((*it)->getClassID() == 1) {
			m_health += (*it)->transferHealth(this);
		}
	}
	// TODO: log all actions
	
	
	
	// TODO: log outcome
	
	m_healthOld = m_health;
	
}

void IntelSheep::move(double dt, World* world) {
	
	m_velocity.normalize(m_speed);	// ANA: intelsheep has a constant speed
									// ANA: velocity direction shall be generated by NN
									
	Thing::move(dt, world);

	m_health -= m_healthConsumption * dt;
	
}



