#include "IntelSheep.h"
#include <algorithm>

IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel) : Thing(pos, vel) {
//~ IntelSheep::IntelSheep(const SpatialVector& pos, const SpatialVector& vel, World* world) : Thing(pos, vel, world) {
	
	m_speed					= 1.0;
	m_friction				= 0.0;
	m_mass					= 100.0;
	m_eatingRange			= 10.0;
	m_perceptionRange		= 50.0;
	m_healthConsumption		= 0.1;
	m_health				= 100.0;
	m_healthOld				= 100.0;
	
	m_classID					= "IntelSheep";
	
	m_log.open("log.txt");
}

IntelSheep::~IntelSheep(){
	m_log.close();
}

void IntelSheep::perceive(World* world) {
	//~ std::list<Thing*> m_thingsInSight
	m_thingsInSight = world->getThings(m_position, m_perceptionRange, m_velocity, M_PI_4);
	
	// NOTE: maybe put filtering for closest object into getThings, add argument unsigned int numClosestObjects, 0 means all
	// NOTE: the intelSheep is confused by more than 10 objects
	const unsigned int maxNumObjects = 10;
	if (m_thingsInSight.size() > maxNumObjects){
		std::vector<double> distances(maxNumObjects, 0.0);
		for(std::list<Thing*>::const_iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
			distances.push_back(((*it)->getPosition() - m_position).length());
		}
		std::sort(distances.begin(), distances.end());
		double threshold = distances[maxNumObjects];
		
		for(std::list<Thing*>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ) {
			
			double distance = ((*it)->getPosition() - m_position).length();
			if (distance > threshold) {
				m_thingsInSight.erase(it);
			} else {
				++it;
			}
		}
	}
	
}

unsigned int convertClassIdToInt(const std::string classID){
	//~ switch (classID) {
		//~ case std::string("Berry"):
			return 1;
			
		//~ case std::string("Wolf"):
			//~ return 2;

		//~ case std::string("Stone"):
			//~ return 3;
			
		//~ case default:
			//~ return 0;	
	//~ }
}

void IntelSheep::logPerception(){
	const unsigned int minNumberObjects = 10;
	for(std::list<Thing*>::iterator it = m_thingsInSight.begin(); it != m_thingsInSight.end(); ++it) {
		m_log << convertClassIdToInt( (*it)->getClassID() ) << " " << (*it)->getPosition() << " ";
	}
}

void IntelSheep::progress(double dt, World* world) {
	
	perceive(world);
	
	// TODO: log all perceptions
	
	
	
	// ANA: AI processing here!
	
	// SG: the most intelligent movement ever:
	m_velocity.randomize();
	move(dt);
	
	std::list<Thing*> thingsInFront = world->getThings(m_position, m_eatingRange, m_velocity, M_PI_4);
	for(std::list<Thing*>::iterator it = thingsInFront.begin(); it != thingsInFront.end(); ++it) {
		// eat the berries!
		if ((*it)->getClassID() == "Berry") {
			m_health += (*it)->transferHealth(this);
		}
	}
	// TODO: log all actions
	
	
	
	// TODO: log outcome
	
	m_healthOld = m_health;
	
}

void IntelSheep::move(double dt) {
	
	m_velocity.normalize(m_speed);	// ANA: intelsheep has a constant speed
									// ANA: velocity direction shall be generated by NN
									
	Thing::move(dt);
	
	
	if(m_health > 1.0) 	
		m_health -= m_healthConsumption * dt;
	
}

void IntelSheep::print(){
	std::vector<double> position = m_position.getCoordinates();
	std::cout << "Thing " << m_identifier << " of type " << m_classID << " at " << position[0] << "," << position[1] << "," << position[2] << " with health " << m_health << std::endl;
	std::vector<double> velocity = m_velocity.getCoordinates();
	m_log << velocity[0] << " " << velocity[1] << " " << velocity[2] << " " << m_health - m_healthOld << std::endl;
	// TODO: output detected object or even better: field of view in pixels when we sense the area
	
	//~ m_log << "Things in sight:" << std::endl;
	//~ m_log << "begin" << std::endl;

	//~ for(std::list<Thing*>::iterator it = thingsInSight.begin(); it != thingsInSight.end(); it++) {
		//~ m_log << "Thing in sight: " << (*it)->print() << 
	//~ }
	
	//~ m_log << "end" << std::endl;
	
	// TODO implement ostream<< operator
	//~ std::cout << "Thing " << m_identifier << "with mass " << m_mass << " at " << m_position << " with health " << m_health << std::endl;
}





