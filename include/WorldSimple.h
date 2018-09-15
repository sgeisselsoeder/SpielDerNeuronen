#ifndef WORLD_SIMPLE_H
#define WORLD_SIMPLE_H

#include <vector>
#include <list>
#include "World.h"
#include <iostream>
#include <fstream>

class WorldSimple : public World
{
private:
    std::list<ThingPtr> m_things;
    double m_time;
    std::ofstream m_logfile;
    
public:
    std::list<ThingPtr> getThings(const SpatialVector& position, double radius, const SpatialVector& direction = SpatialVector(1,1,1), 
                                  double observationAngle = 6.284 /*two pi by default*/, unsigned int thingType = 0);
    
    WorldSimple(const std::string& logfile = "world_logfile.log");
    
    ~WorldSimple();
    
    void progress(double t);
    
    void addToWorld(ThingPtr t);
    
    void printThings(std::ostream& outstream = std::cout);
	
};

#endif
