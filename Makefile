OBJECTS = bin/WorldSimple.o bin/SpatialVector.o bin/Thing.o bin/IntelSheep.o bin/Berry.o
INCLUDEDIRS = -I ./include
CXXFLAGS = -g $(INCLUDEDIRS)


all: UniverseOfIntelSheep

UniverseOfIntelSheep: ${OBJECTS}
	g++ $(CXXFLAGS) -o bin/UniverseOfIntelSheep src/UniverseOfIntelSheep.cpp $(OBJECTS)

bin/WorldSimple.o: src/Thing.cpp src/WorldSimple.cpp
	g++ $(CXXFLAGS) -c -o bin/WorldSimple.o src/WorldSimple.cpp
	
bin/SpatialVector.o: src/SpatialVector.cpp
	g++ $(CXXFLAGS) -c -o bin/SpatialVector.o src/SpatialVector.cpp
	
bin/IntelSheep.o: src/IntelSheep.cpp src/Thing.cpp
	g++ $(CXXFLAGS) -c -o bin/IntelSheep.o src/IntelSheep.cpp
	
bin/Thing.o: src/Thing.cpp
	g++ $(CXXFLAGS) -c -o bin/Thing.o src/Thing.cpp
	
bin/Berry.o: src/Berry.cpp src/Thing.cpp
	g++ $(CXXFLAGS) -c -o bin/Berry.o src/Berry.cpp

clean:
	rm -f bin/*.o bin/UniverseOfIntelSheep
