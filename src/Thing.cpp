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
	move(dt);
}


void Thing::move(double dt) {
	
	SpatialVector positionUpdate = m_velocity;
	SpatialVector velocityUpdate = m_velocity;
	
	positionUpdate.rescale(dt);
	velocityUpdate.rescale(dt*m_friction/m_mass);
	
	m_position += positionUpdate;
	m_velocity -= velocityUpdate;  //de-acceleration by friction
	 
}

Thing::Thing(const SpatialVector& pos, const SpatialVector& vel) : m_position(pos), m_velocity(vel) {
//~ Thing::Thing(const SpatialVector& pos, const SpatialVector& vel, World* world) : m_position(pos), m_velocity(vel), m_world(world) {
	
}

Thing::Thing(){
	
}

Thing::~Thing(){
	
}

double Thing::getMass() const {
	return m_mass;
}

void Thing::print(){
	std::vector<double> position = m_position.getCoordinates();
	std::cout << "Thing " << m_identifier << " of type " << m_classID << " at " << position[0] << "," << position[1] << "," << position[2] << " with health " << m_health << std::endl;
	// TODO implement ostream<< operator
	//~ std::cout << "Thing " << m_identifier << "with mass " << m_mass << " at " << m_position << " with health " << m_health << std::endl;
}

std::string Thing::getClassID() const {
	return m_classID;
}

double Thing::transferHealth(const Thing* healthSucker) {
	
	return 0.0;		// ANA: a plain thing cannot be eaten
	
}

double Thing::getHealth() const {
	
	return m_health;
	
}
