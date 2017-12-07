#include <vector>
#include "WorldSimple.h"
#include <iostream>

//returns all the objects within a sector
std::list<ThingPtr> WorldSimple::getThings(const SpatialVector& position, double radius, const SpatialVector& direction, double observationAngle, unsigned int thingType) {
	
    std::list<ThingPtr> ret;
    if (direction == SpatialVector(0.0, 0.0, 0.0) ) {
		throw("I need a direction");
		return ret;
	}
    
    // iterate over all the objects
    for (std::list<ThingPtr>::const_iterator it = m_things.begin(); it != m_things.end(); ++it) {
        
        // process those within the radius
        SpatialVector otherPosition( (*it)->getPosition() );
        
        if (otherPosition != position) {
        
			if (distance(position, otherPosition) < radius) {
				
				// evaluate the angle between line of sight (dir) and line towards thing
				SpatialVector otherDirection(otherPosition);
				otherDirection -= position;
				
				double angleBetween = angle(direction, otherDirection);
				//std::cout << "Found an object within the radius at angle " << angleBetween << " obersevationAngle = " << observationAngle << std::endl;        
				if (angleBetween <= observationAngle) {
					//if (angle(direction, otherDirection) <= observationAngle) {
					
					if ((*it)->getClassID() == thingType || thingType == 0) {
						ret.push_back(*it);
					}
					
				}	
			}
		}
    }
    
    return ret;
    
}


void WorldSimple::progress(double dt){
	
	for (std::list<ThingPtr>::iterator it = m_things.begin(); it != m_things.end();) {
		
		if ((*it)->getHealth() <= 0.0) {
			
			// delete (*it);
			it = m_things.erase(it);
			
		} else {
		
			(*it)->progress(dt, this);
			++it;
		
		}
		
	}
	
	m_time += dt;
	
}

void WorldSimple::addToWorld(ThingPtr t)
{
	m_things.push_back(t);
}

void WorldSimple::printThings(){
	for (std::list<ThingPtr>::iterator it = m_things.begin(); it != m_things.end(); ++it){
		(*it)->print();
	}
}


