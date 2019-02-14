#include "UniverseOfIntelSheep.h"

int main() {
	
	WorldSimple ws;
	
	ws.addToWorld(std::make_shared<IntelSheep>(SpatialVector(0.0), SpatialVector(1.0)));
	ws.addToWorld(std::make_shared<Berry>(SpatialVector(25.0, 25.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(35.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(2.0, 2.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(5.0, 5.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Wolf>(SpatialVector(-69.0, 0.0, 79.0), SpatialVector(0.1)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(22.0, 22.0), SpatialVector(0.0)));
	
	unsigned int numTimesteps = 1;
	try {
		for (unsigned int i = 0; i < numTimesteps; ++i){
			std::cout << "Timestep " << i << "/" << numTimesteps << std::endl;
			ws.printThings();
			ws.progress(1.0);
		}
	} catch (const std::exception& ex) {
			std::cout << "Failed with " << ex.what() << std::endl;
			throw(ex);
	}	
	
}

