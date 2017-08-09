#include <vector>
#include "WorldSimple.h"

//returns all the objects within a sector
std::list<ThingPtr> WorldSimple::getThings(const SpatialVector& position, double radius, const SpatialVector& direction, double observationAngle, std::string thingType) {
    
    std::list<ThingPtr> ret;
    
    // iterate over all the objects
    for (std::list<ThingPtr>::const_iterator it = m_things.begin(); it != m_things.end(); ++it) {
        
        // process those within the radius
        SpatialVector otherPosition( (*it)->getPosition() );
        
        if (distance(position, otherPosition) < radius) {             
			
			// evaluate the angle between line of sight (dir) and line towards thing
			SpatialVector otherDirection(otherPosition);
			otherDirection -= position;
			
			if (angle(direction, otherDirection) < observationAngle) {
				
				if ((*it)->getClassID() == thingType || thingType == "") {
					ret.push_back(*it);
				}
				
			}	
		}
    }
    
    return ret;
    
}


void WorldSimple::progress(double dt){
	
	for (std::list<ThingPtr>::iterator it = m_things.begin(); it != m_things.end();) {
		
		if ((*it)->getHealth() < 0.1) {
			
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


