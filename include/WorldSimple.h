#ifndef WORLD_SIMPLE_H
#define WORLD_SIMPLE_H

#include <vector>
#include <list>
#include "World.h"

class WorldSimple : public World
{
private:
    std::list<Thing*> m_things;
    double m_time;
    
public:
    std::list<Thing*> getThings(const SpatialVector& position, double radius, const SpatialVector& direction, double observationAngle);
    
    std::list<Thing*> getThings(std::string thingType);
    
    void progress(double t);
    
    void addToWorld(Thing* t);
    
    void printThings();
};

#endif
