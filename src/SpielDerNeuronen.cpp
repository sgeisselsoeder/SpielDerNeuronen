#include <iostream>

#include "WorldSimple.h"
#include "AllThings.h"

using namespace std;

int main()
{
	cout << "Starting the world" << endl;
	
	WorldSimple ws;
	ws.addToWorld(Stone());
	
	unsigned int numTimesteps = 100;
	for (unsigned int i = 0; i < numTimesteps; ++i){
		std::cout << "Timestep " << i << "/" << numTimesteps << std::endl;
		ws.printThings();
		ws.progress(0.1);
	}
	
	return 0;
}




