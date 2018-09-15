#include "Wolf.h"
#include <algorithm>
#include <limits>

Wolf::Wolf(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
//~ Wolf::Wolf(const SpatialVector& pos, const SpatialVector& vel, World* world) : Thing(pos, vel, world) {
	
	m_speed					= 1.5;
	m_friction				= 0.0;
	m_mass					= 100.0;
	m_eatingRange			= 2.0;	// any interaction range must be at least twice the collision radius (1.0 at this moment)
	m_perceptionRange		= 200.0;
	m_perceptionAngle		= 2.0*M_PI;
	m_healthConsumption		= 0.1;
	m_health				= 100.0;
	m_healthOld				= m_health;
	
	m_classID				= 2;
	
	m_log.open("logWolf.txt");
}

Wolf::~Wolf(){
	m_log.close();
}

void Wolf::perceive(World* world) {
	//~ std::list<ThingPtr> m_thingsInSight
	
	m_thingsInSight = world->getThings(m_position, m_perceptionRange, m_velocity, m_perceptionAngle);
	//std::cout << "Number of percieved objects " << m_thingsInSight.size() << std::endl;
	
	// NOTE: maybe put filtering for closest object into getThings, add argument unsigned int numClosestObjects, 0 means all
	
	// NOTE: For now, the Wolf is confused by more than 10 objects
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
void Wolf::logPerception(){
	//m_log << "Perception: " << std::endl;
	// Percieve as many objects as are around
	for(std::list<ThingPtr>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
		//std::cout << (*it)->getClassID() << " " << ((*it)->getPosition() - m_position) << std::endl;
		m_log << (*it)->getClassID() << " " << ((*it)->getPosition() - m_position) << " ";
	}
	const unsigned int minNumberObjects = 10;
	// Always write AT LEAST the required number of objects
	for(unsigned int i = 0; i < (minNumberObjects-m_thingsInSight.size()); ++i ) {
		//std::cout << 0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
		m_log << 0 << " " << 0.0 << " " << 0.0 << " " << 0.0 << " ";
	}
	m_log << std::endl;
	
}

// Log the status to file
void Wolf::logStatus(){
	/*
	m_log << "Object: " << std::endl;
	m_log << m_classID << " " << m_health << " " << m_position << " " << m_velocity << std::endl;
	*/
	m_log << m_health << " " << m_position << " " << m_velocity << " ";
}

void Wolf::comeUpWithPlan() {
	// ANA: AI processing here!
	
	// SG: by default: the most intelligent movement ever:
	m_velocity.randomize();
	SpatialVector randomDirection = m_velocity;
	
	// but also: check all percieved objects
	double distanceToClosestSheepSoFar = std::numeric_limits<double>::max();
	for(std::list<ThingPtr>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {		
		// std::cout << "Wolf found an object of class " << (*it)->getClassID() << std::endl;
		// act on sheep
		if ((*it)->getClassID() == 5) {
			// how far is it to this sheep
			double distanceToThisSheep = distance(m_position, (*it)->getPosition());
			// std::cout << "Found a sheep at distance " << distanceToThisSheep << " best so far: " << distanceToClosestSheepSoFar << std::endl;
			// have we seen a closer one?
			if (distanceToThisSheep < distanceToClosestSheepSoFar) {
				// we want to go to this sheep! It's delicious
				distanceToClosestSheepSoFar = distanceToThisSheep;
				m_velocity = (*it)->getPosition()-m_position;
				// but also add some randomness
				// randomDirection.normalize(0.1 * m_velocity.length());
				// m_velocity += randomDirection;
				// std::cout << " moving from " << m_position << " to " << (*it)->getPosition() << " in direction " << m_velocity << std::endl;
			}
		}
	}
	
}

void Wolf::progress(double dt, World* world) {
	
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
	// std::cerr << "progress vor thingsInFront" << std::endl;
	std::list<ThingPtr> thingsInFront = world->getThings(m_position, m_eatingRange, m_velocity, m_perceptionAngle);
	for(std::list<ThingPtr>::iterator it = thingsInFront.begin(); it != thingsInFront.end(); ++it) {
		// eat the sheep (sheep class ID = 4)!
		if ((*it)->getClassID() == 5) {
			m_health += (*it)->transferHealth(this);
		}
	}
	// TODO: log all actions
	
	
	
	// TODO: log outcome
	
	m_healthOld = m_health;
	
}

void Wolf::move(double dt, World* world) {
	
	m_velocity.normalize(m_speed);	// ANA: Wolf has a constant speed
									// ANA: velocity direction shall be generated by NN
									
	Thing::move(dt, world);

	m_health -= m_healthConsumption * dt;
	
}



