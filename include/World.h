// an interface for a container for all the things in the universe
// overload the virtual functions with specific implementations


#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <list>
#include "Thing.h"
#include <memory>
#include <iostream>
#include <fstream>

class Thing;

class World {
 
public:
    
    virtual std::list<ThingPtr> getThings(const SpatialVector&, double, const SpatialVector& direction = SpatialVector(1,1,1), double = 6.284 /*two pi by default*/, unsigned int = 0) = 0;       	// returns a list within a sector
    
																													// Note: functions like look()
																													// shall provide further 
																													// object filtering depending on
																													// perception properties
    
    virtual void progress(double) = 0;                                // iterates over all the things
                                                                            // in the universe and calls
                                                                            // their progress() functions
                                                                            // checks if the thing moves
                                                                            // to another quadrant etc
                                                                            
    virtual void addToWorld(ThingPtr t) = 0;
    
    
    virtual void printThings(std::ostream& outstream = std::cout) = 0;
    
    virtual ~World();

};

#endif

