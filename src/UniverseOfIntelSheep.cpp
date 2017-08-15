#include "UniverseOfIntelSheep.h"

int main() {
	
	WorldSimple ws;
	
	ws.addToWorld(std::make_shared<IntelSheep>(SpatialVector(0.0), SpatialVector(1.0)));
	ws.addToWorld(std::make_shared<Berry>(SpatialVector(25.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(35.0), SpatialVector(0.0)));
	
	unsigned int numTimesteps = 100;
	for (unsigned int i = 0; i < numTimesteps; ++i){
		std::cout << "Timestep " << i << "/" << numTimesteps << std::endl;
		ws.printThings();
		ws.progress(1.0);
	}
	
	
	
	
}

