#include "UniverseOfIntelSheep.h"

int main() {
	
	WorldSimple ws;
	
	ws.addToWorld(std::make_shared<IntelSheep>(SpatialVector(0.0), SpatialVector(1.0)));
	ws.addToWorld(std::make_shared<Berry>(SpatialVector(25.0, 25.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(35.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(2.0, 2.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(5.0, 5.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(9.0, 9.0), SpatialVector(0.0)));
	ws.addToWorld(std::make_shared<Stone>(SpatialVector(22.0, 22.0), SpatialVector(0.0)));
	
	unsigned int numTimesteps = 200;
	for (unsigned int i = 0; i < numTimesteps; ++i){
		std::cout << "Timestep " << i << "/" << numTimesteps << std::endl;
		ws.printThings();
		ws.progress(1.0);
	}
	
	
	
	
}

