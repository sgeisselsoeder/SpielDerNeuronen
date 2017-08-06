// an interface for a container for all the things in the universe
// overload the virtual functions with specific implementations



#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <list>
//~ #include "SpatialVector.h"
#include "Thing.h"
// #include "AllThings.h"    |  ANA: moved to SpielDerNeuronen; the structure is hell :(


class Thing;

class World {
 
public:
    
    virtual std::list<Thing*> getThings(const SpatialVector&, double, const SpatialVector&, double, std::string = "") = 0;       	// returns a list within a sector
    
																													// Note: functions like look()
																													// shall provide further 
																													// object filtering depending on
																													// perception properties
    
    virtual void progress(double) = 0;                                // iterates over all the things
                                                                            // in the universe and calls
                                                                            // their progress() functions
                                                                            // checks if the thing moves
                                                                            // to another quadrant etc
                                                                            
    virtual void addToWorld(Thing*) = 0;
    
    virtual void printThings() = 0;
    
};

#endif

