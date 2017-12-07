#include "SpatialVector.h"
#include "Thing.h"
#include <iostream>

SpatialVector Thing::getPosition() const {
    return m_position;
}

Thing::Thing(SpatialVector position, SpatialVector velocity, double mass, double health, double maxHealth, double maxSpeed){
	m_position = position;
	m_velocity = velocity;
	m_mass = mass;
	m_health = health;
	m_maxHealth = maxHealth;
	m_maxSpeed = maxSpeed;
}

// ANA: a plain thing is just an inertial body
void Thing::progress(double dt, World* world) {
	move(dt, world);
}


void Thing::move(double dt, World* world) {
	
	SpatialVector positionUpdate = m_velocity;
	SpatialVector velocityUpdate = m_velocity;
	
	positionUpdate.rescale(dt);
	velocityUpdate.rescale(dt*m_friction/m_mass);
	
	m_position += positionUpdate;
	m_velocity -= velocityUpdate;  //de-acceleration by friction
	
	//ANA: plain things cannot go through things
	//ANA: if a certain thing shall be able to, override this function
	double collisionRadius = 1.0;
	std::list<ThingPtr> lst = world->getThings(m_position, collisionRadius);
	
	if (!lst.empty()) {
		m_position -= positionUpdate;
	}
	 
}

Thing::Thing(const SpatialVector& pos, const SpatialVector& vel) : m_position(pos), m_velocity(vel) {

	Thing();
	
}

Thing::Thing() {
	
	m_collisionRadius = 5.0;
	
}

Thing::~Thing() {
	
}

double Thing::getMass() const {
	return m_mass;
}

void Thing::print() {
	std::vector<double> position = m_position.getCoordinates();
	std::cout << "Thing " << m_identifier << " of type " << convertClassIdToString(m_classID) << " at " << position[0] << "," << position[1] << "," << position[2] << " with health " << m_health << std::endl;
	// TODO implement ostream<< operator
	//~ std::cout << "Thing " << m_identifier << "with mass " << m_mass << " at " << m_position << " with health " << m_health << std::endl;
}

unsigned int Thing::getClassID() const {
	return m_classID;
}

double Thing::transferHealth(const Thing* healthSucker) {
	
	return 0.0;		// ANA: a plain thing cannot be eaten
	
}

double Thing::getHealth() const {
	
	return m_health;
	
}

// converts integer ID into a string description
std::string convertClassIdToString(const unsigned int classID) {
	switch (classID) {
		case 1:
			return std::string("Berry");
			
		case 2:
			return std::string("Wolf");

		case 3:
			return std::string("Stone");
			
		case 4:
			return std::string("Sheep");
			
		case 5:
			return std::string("IntelSheep");
			
		default:
			return std::string("");	
	}
}
