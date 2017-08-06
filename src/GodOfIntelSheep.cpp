#include "GodOfIntelSheep.h"

int main() {
	
	WorldSimple ws;
	
	ws.addToWorld(new IntelSheep(SpatialVector(0.0), SpatialVector(1.0)));
	
	ws.addToWorld(new Berry(SpatialVector(25.0), SpatialVector(0.0)));
	
	unsigned int numTimesteps = 100;
	for (unsigned int i = 0; i < numTimesteps; ++i){
		std::cout << "Timestep " << i << "/" << numTimesteps << std::endl;
		ws.printThings();
		ws.progress(1.0);
	}
	
	
	
	
}

